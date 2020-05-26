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
    std::cout<<"Receiver running \n";
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
    else
    {
        std::cout<<"Receiver got nullptr\n";
    }
    

}