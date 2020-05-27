#ifndef CLIENT_SENDER_H
#define CLIENT_SENDER_H

#include <netdb.h>
#include <arpa/inet.h>
#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "packets.h"

class ClientSender
{
private:
    int& sockfd;
    sockaddr_in6& serverAddr;
    socklen_t serverLen;
    bool * isExitRequested;
    std::queue<std::shared_ptr<Packet> > packets;
    void sendToServer(std::shared_ptr<Packet> p);
public:
    
    bool isQueueNotEmpty();
    std::shared_ptr<Packet> popFromQueue();
    void addToQueue(std::shared_ptr<Packet> p);

    ClientSender(int& sockfd, sockaddr_in6& serverAddr, bool * exitPointer);
    int sendAck(int noAck);
    int sendAuth(std::string password);
    int sendRdy(bool ready);
    int sendRenew();
    int sendDisconnect();
    void operator()();
    void runOnce();
    ~ClientSender();
};


#endif