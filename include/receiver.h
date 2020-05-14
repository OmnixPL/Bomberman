#ifndef RECEIVER_H
#define RECEIVER_H
#include <map>
#include <iostream>
#include <netdb.h>
#include <arpa/inet.h>
#include "packets.h"


class Receiver
{
private:
    int& sockfd;
    std::vector<Packet> packets;
    std::map<packet_t, int> typeToBehaviour;
    virtual void defaultBehaviour() = 0;
    sockaddr_in6 addr;
public:
    bool isExitRequested = false;
    Receiver(int& sockfd, char* address, int port);
    void serve();
    virtual ~Receiver();
};


#endif