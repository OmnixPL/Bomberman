// Szymon Malolepszy
// Kacper Kula
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

#include "client.h"
#include "include/packets.h"

using clock_type = std::chrono::high_resolution_clock;


// grabs from server.cpp 
void printPacket(std::shared_ptr<Packet> p);

Client::Client(
            int version, 
            const char* addr, 
            int port, 
            std::string username, 
            std::string pathToMoves,
            int noSecondsBetweenMoves) {
    servaddr.sin6_family = AF_INET6; /* change for ipv6 */
    inet_pton(AF_INET6, addr, &servaddr.sin6_addr);
    servaddr.sin6_port = htons(port);

    if ((cliSockfd = socket(AF_INET6, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        return;
    }

    model = new Model(username);
    
    sender = new ClientSender(cliSockfd, servaddr, &isExitRequested);
    receiver = new ClientReceiver(cliSockfd, servaddr, &isExitRequested);
    controller = new Controller(pathToMoves,sender, model, &isExitRequested, noSecondsBetweenMoves);
}

void Client::runSequential()
{   
    auto last_timepoint = clock_type::now();
    auto current_timepoint = clock_type::now();
    while (!isExitRequested || sender->isQueueNotEmpty())
    {
        sender->runOnce();
        receiver->runOnce();
        current_timepoint = clock_type::now();
        if(current_timepoint - last_timepoint >= std::chrono::milliseconds(controller->getNoSeconds()))
        {
            std::cout<<"Controller running\n";
            controller->runOnce();
            last_timepoint = clock_type::now();
        }
    }
    
}