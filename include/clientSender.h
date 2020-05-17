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
    sockaddr_in6 addr;
    
    void sendToServer(Packet p);
public:
    std::queue<Packet> packets;
    ClientSender(int& sockfd, char* address, int port);
    void operator()();
    ~ClientSender();
};


#endif