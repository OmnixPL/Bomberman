#ifndef CLIENT_SENDER_H
#define CLIENT_SENDER_H

#include <netdb.h>
#include <arpa/inet.h>
#include <iostream>
#include <queue>
#include <mutex>
#include "packets.h"

class ClientSender
{
private:
    int& sockfd;
    sockaddr_in6 addr;
    std::mutex * queueMutex;
    
    void sendToServer(Packet p);
    std::queue<Packet*> packets;
public:
    
    ClientSender(int& sockfd, char* address, int port, std::mutex & mutex);
    void addToQueue(Packet * p);
    Packet* popFromQueue();
    void operator()();
    ~ClientSender();
};


#endif