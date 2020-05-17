#include <clientSender.h>
#include <client.h>

ClientSender::ClientSender(int& sockfd, char* address, int port) : sockfd(sockfd)
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
    packets.push(PacketAck(4, "testUser"));

    while (!packets.empty())
    {
        sendToServer(packets.front());
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

