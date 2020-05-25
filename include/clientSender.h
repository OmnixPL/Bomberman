#ifndef CLIENT_SENDER_H
#define CLIENT_SENDER_H

#include <netdb.h>
#include <arpa/inet.h>
#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include "packets.h"

class ClientSender
{
private:
    int& sockfd;
    sockaddr_in6& serverAddr;
    socklen_t serverLen;
    std::mutex * queueMutex;
    bool * isExitRequested;
    
    void sendToServer(std::shared_ptr<Packet> p);
    std::queue<std::shared_ptr<Packet> > packets;
public:
    std::shared_ptr<Packet> popFromQueue();
    void addToQueue(std::shared_ptr<Packet> p);

    ClientSender(int& sockfd, sockaddr_in6& serverAddr, std::mutex &mutex, bool * exitPointer);
    int sendAck(int noAck);
    int sendAuth(std::string password);
    int sendRdy(bool ready);
    int sendRenew();
    int sendDisconnect();
    void operator()();
    ~ClientSender();
};


#endif