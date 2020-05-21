#ifndef CLIENT_SENDER_H
#define CLIENT_SENDER_H

#include <netdb.h>
#include <arpa/inet.h>
#include <iostream>
#include <queue>
#include "packets.h"

class ClientSender
{
private:
    int& sockfd;
    sockaddr_in6& serverAddr;
    socklen_t serverLen;
    
    void sendToServer(Packet p);
public:
    std::queue<Packet> packets;
    ClientSender(int& sockfd, char* address, int port);
    ClientSender(int& sockfd, sockaddr_in6& serverAddr);
    int sendAck(int noAck);
    int sendAuth(std::string password);
    int sendRdy(bool ready);
    int sendRenew();
    int sendDisconnect();
    void operator()();
    ~ClientSender();
};


#endif