#include <clientSender.h>
#include <client.h>

ClientSender::ClientSender(int& sockfd, char* address, int port, std::mutex & mutex) : sockfd(sockfd), queueMutex(&mutex)
{
    addr.sin6_family = AF_INET6;
    inet_pton(AF_INET6, address, &addr.sin6_addr);
    addr.sin6_port = htons(port);
}

ClientSender::~ClientSender()
{
    std::cout<<"Destroying ClientSender object";
}

void ClientSender::operator()()
{
    packets.push(new PacketAck(4, "testUser"));

    while (!packets.empty())
    {
        // Packet * p = popFromQueue();
        Packet * p = packets.front();
        sendToServer(*p);
        packets.pop();
    }
    
}

void ClientSender::sendToServer(Packet p)
{
    char b[BUFFERSZ];
    p.serialize(b, BUFFERSZ);
    std::cout<<"Send packet: "<<b<<std::endl;
    sendto(sockfd, b, sizeof(p), 0, (const struct sockaddr *) &addr, sizeof(addr));
}


void ClientSender::addToQueue(Packet * p)
{
    // this will be destroyed, when the function exits
    std::lock_guard<std::mutex> lockGuard(*queueMutex);
    packets.push(p);
}

Packet* ClientSender::popFromQueue()
{
    // this will be destroyed, when the function exits
    std::lock_guard<std::mutex> lockGuard(*queueMutex);
    Packet * result = packets.front();
    packets.pop();
    return result;
}


