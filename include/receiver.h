#ifndef RECEIVER_H
#define RECEIVER_H
#include<map>
#include<iostream>
#include"packets.h"


class Receiver
{
private:
    int& servSockfd;
    std::vector<Packet>& packets;
    std::map<packet_t, int> typeToBehaviour;
    virtual void defaultBehaviour() = 0;
public:
    Receiver(int& sservSockfd, std::vector<Packet>& ppackets);
    void serve();
    virtual ~Receiver();
};


#endif