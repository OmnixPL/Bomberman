#ifndef CLIENT_RECEIVER_H
#define CLIENT_RECEIVER_H

#include "receiver.h"

class ClientReceiver : public Receiver
{
private:
    void defaultBehaviour(char* buffer, size_t len);
public:
    ClientReceiver(int& cliSockfd, char* address, int port, struct timeval timeout);
    ~ClientReceiver();
};


#endif