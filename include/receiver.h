#ifndef RECEIVER_H
#define RECEIVER_H
#include <map>
#include <iostream>
#include <netdb.h>
#include <arpa/inet.h>
#include <functional>
#include "packets.h"



class Receiver
{
private:
    int& sockfd;
    std::vector<Packet> packets;
    std::map<packet_t, std::function<void(char *, size_t)> > typeToBehaviour;
    virtual void defaultBehaviour(char* buffer, size_t len) = 0;
    sockaddr_in6 addr;
public:
    bool isExitRequested = false;
    Receiver(int& sockfd, char* address, int port);
    void operator()();
    virtual ~Receiver();
};


#endif