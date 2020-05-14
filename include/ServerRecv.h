#include <iostream>
#include "packets.h"
#include "receiver.h"

class ServerRecv : public Receiver {
private:
    void defaultBehaviour(char* buffer, size_t len)
    {
        // TODO implement
    }
public:
    ServerRecv(int& sservSockfd, char* address, int port);
    ~ServerRecv(){};
};