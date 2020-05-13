#ifndef CLIENT_RECEIVER_H
#define CLIENT_RECEIVER_H

#include "receiver.h"

class ClientReceiver : public Receiver
{
private:
    void defaultBehaviour();
public:
    ClientReceiver(int& sservSockfd, std::vector<Packet>& ppackets);
    ~ClientReceiver();
};


#endif