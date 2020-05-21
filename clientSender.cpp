#include <clientSender.h>
#include <client.h>

ClientSender::ClientSender(int& ssockfd, sockaddr_in6& sserverAddr) : sockfd(ssockfd), serverAddr(sserverAddr) {
    serverLen = sizeof(serverAddr);
}

ClientSender::~ClientSender() {}

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
    sendto(sockfd, b, sizeof(p), 0, (const struct sockaddr *) &serverAddr, sizeof(serverAddr));
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