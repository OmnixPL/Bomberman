#ifndef CLIENT_RECEIVER_H
#define CLIENT_RECEIVER_H

#include "receiver.h"

class ClientReceiver : public Receiver
{
private:
    void defaultBehaviour();
public:
    ClientReceiver(int& cliSockfd, char* address, int port);
    ~ClientReceiver();
};


#endif