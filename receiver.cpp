#include <map>
#include <iostream>
#include "packets.h"
#include "receiver.h"
#include "client.h"

Receiver::Receiver(int& sservSockfd, std::vector<Packet>& ppackets) : servSockfd(sservSockfd), packets(ppackets)
{
    ;
}

Receiver::~Receiver(){std::cout<<"Whatever";};

void Receiver::serve()
{
    int i = 10;
    char buffer[BUFFERSZ];
    while (i--)
    {
        ;
    }
    
}