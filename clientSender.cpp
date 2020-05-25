#include <clientSender.h>
#include <client.h>

ClientSender::ClientSender(int& ssockfd, sockaddr_in6& sserverAddr, std::mutex &mutex, bool * exitPointer) : 
    sockfd(ssockfd), 
    serverAddr(sserverAddr),
    queueMutex(&mutex),
    isExitRequested(exitPointer)
{
    serverLen = sizeof(serverAddr);
}

ClientSender::~ClientSender() {}

void ClientSender::operator()()
{
    while (!(*isExitRequested) && !packets.empty())
    {
        std::cout<<"Client: sending packet\n";
        std::shared_ptr<Packet> p = popFromQueue();
        sendToServer(p);
    }
}

std::shared_ptr<Packet> ClientSender::popFromQueue()
{
    std::lock_guard<std::mutex>(*queueMutex);
    std::shared_ptr<Packet> result = packets.front();
    packets.pop();
    return result;
}
void ClientSender::addToQueue(std::shared_ptr<Packet> p)
{
    std::lock_guard<std::mutex>(*queueMutex);
    packets.push(p);
}

void ClientSender::sendToServer(std::shared_ptr<Packet> p)
{
    char b[BUFFERSZ];
    int count = p->serialize(b, BUFFERSZ);
    sendto(sockfd, b, count, 0, (const struct sockaddr *) &serverAddr, sizeof(serverAddr));
}

int ClientSender::sendAck(int noAck) {
    char buffer[BUFFERSZ];
    PacketAck ack(noAck);

    ack.serialize(buffer, BUFFERSZ);
    if( sendto(sockfd, buffer, sizeof(ack), 0, (const struct sockaddr *) &serverAddr, serverLen) < 0)
        return -1;

    return 0;
}

int ClientSender::sendAuth(std::string password) {
    char buffer[BUFFERSZ];
    PacketAuth auth(password);

    auth.serialize(buffer, BUFFERSZ);
    if( sendto(sockfd, buffer, sizeof(auth), 0, (const struct sockaddr *) &serverAddr, serverLen) < 0)
        return -1;

    return 0;
}

int ClientSender::sendRdy(bool ready) {
    char buffer[BUFFERSZ];
    PacketRdy rdy(ready);

    rdy.serialize(buffer, BUFFERSZ);
    if( sendto(sockfd, buffer, sizeof(rdy), 0, (const struct sockaddr *) &serverAddr, serverLen) < 0)
        return -1;

    return 0;
}

int ClientSender::sendRenew() {
    char buffer[BUFFERSZ];
    PacketRenew renew;

    renew.serialize(buffer, BUFFERSZ);
    if( sendto(sockfd, buffer, sizeof(renew), 0, (const struct sockaddr *) &serverAddr, serverLen) < 0)
        return -1;

    return 0;
}

int ClientSender::sendDisconnect() {
    char buffer[BUFFERSZ];
    PacketDisconnect dc;

    dc.serialize(buffer, BUFFERSZ);
    if( sendto(sockfd, buffer, sizeof(dc), 0, (const struct sockaddr *) &serverAddr, serverLen) < 0)
        return -1;

    return 0;
}