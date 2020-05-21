#ifndef CLIENT_RECEIVER_H
#define CLIENT_RECEIVER_H

#include <memory>
#include "receiver.h"

#define BUFFERSZ 512

class ClientReceiver /*: public Receiver */
{
private:
    int& cliSockfd;
    sockaddr_in6& servaddr;
    socklen_t serverLen;

    bool isPacketOK(std::shared_ptr<Packet> packet);
    // void defaultBehaviour(char* buffer, size_t len);
public:
    // ClientReceiver(int& cliSockfd, char* address, int port, struct timeval timeout);
    ClientReceiver(int& cliSockfd, sockaddr_in6& servaddr);
    ~ClientReceiver();

    std::shared_ptr<Packet> grabPacket();   // currently returns packet but can be easily added to queue if needed
};


#endif