#ifndef RECEIVER_H
#define RECEIVER_H
#include <map>
#include <iostream>
#include <netdb.h>
#include <arpa/inet.h>
#include <functional>
#include <memory>
#include "packets.h"



class Receiver
{
protected:
    int& mySockfd;
    sockaddr_in6& targetAddr;
    socklen_t serverLen;
    std::map<packet_t, std::function< void(std::shared_ptr<Packet>) > > typeToBehaviour;
    virtual void defaultBehaviour(std::shared_ptr<Packet> packet) = 0;
    virtual std::shared_ptr<Packet> grabPacket() = 0;
public:
    bool isExitRequested = false;
    Receiver(int& cliSockfd, sockaddr_in6& servaddr);
    
    void operator()();
    virtual ~Receiver();
};


#endif