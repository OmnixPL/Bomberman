#include <map>
#include <iostream>
#include "packets.h"
#include "receiver.h"
#include "client.h"

Receiver::Receiver(int& sockfd, char* address, int port) : sockfd(sockfd)
{
    addr.sin6_family = AF_INET6;
    inet_pton(AF_INET6, address, &addr.sin6_addr);
    addr.sin6_port = htons(port);
}

Receiver::~Receiver(){std::cout<<"Whatever";};

void Receiver::serve()
{
    char buffer[BUFFERSZ];
    int readCount = recvfrom(sockfd, buffer, BUFFERSZ, 0, (struct sockaddr*) &addr, (socklen_t *)sizeof(addr));
    packet_t typeOfPacketReceived = Packet::extractType(buffer, BUFFERSZ);
    while (!isExitRequested)
    {
        // if there's no such type in map, perform default behaviour
        if(typeToBehaviour.find(typeOfPacketReceived) == typeToBehaviour.end())
        {
            defaultBehaviour(buffer, BUFFERSZ);
        }
        else
        {
            typeToBehaviour[typeOfPacketReceived](buffer, BUFFERSZ);
        }
    }
    
    
}