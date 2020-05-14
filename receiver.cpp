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
    int i = 10;
    char buffer[BUFFERSZ];
    while (i--)
    {
        int readCount = recvfrom(sockfd, buffer, BUFFERSZ, 0, (struct sockaddr*) &addr, (socklen_t *)sizeof(addr));
        Packet p(buffer, BUFFERSZ);
        std::cout << "Incoming packet type: " << p.getType() << std::endl; 
        std::cout << "User: " << p.getUser() << std::endl;
        std::cout << "NO: " << p.getNo() << std::endl;
    }
    
}