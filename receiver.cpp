#include <map>
#include <iostream>
#include "packets.h"
#include "receiver.h"
#include "client.h"

Receiver::Receiver(int& cliSockfd, sockaddr_in6& servaddr, bool * exitPointer) : 
    mySockfd(cliSockfd),
    targetAddr(servaddr),
    serverLen(sizeof(servaddr)),
    isExitRequested(exitPointer)
{}

Receiver::~Receiver(){std::cout<<"Destroying receiver object";};

void Receiver::operator()()
{
    while (!(*isExitRequested))
    {
        std::shared_ptr<Packet> packet = grabPacket();
        if(packet != nullptr)
        {
            packet_t type = packet->getType();
            // no behaviour for such type
            if(typeToBehaviour.find(type) == typeToBehaviour.end())
            {
                defaultBehaviour(packet);
            }
            else
            {
                typeToBehaviour[type](packet);
            }
        }        
        
    }
}

void Receiver::runOnce()
{
    if(*isExitRequested)
    {
        return;
    }
    std::shared_ptr<Packet> packet = grabPacket();
    while (packet != nullptr)
    {
        packet_t type = packet->getType();
        // no behaviour for such type
        if(typeToBehaviour.find(type) == typeToBehaviour.end())
        {
            defaultBehaviour(packet);
        }
        else
        {
            typeToBehaviour[type](packet);
        }
        packet = grabPacket();
    }
}