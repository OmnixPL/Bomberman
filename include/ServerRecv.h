#include <iostream>
#include "packets.h"
#include "receiver.h"

class ServerRecv : public Receiver {
private:
    void defaultBehaviour()
    {
        // TODO implement
    }
public:
    ServerRecv(int& sservSockfd, std::vector<Packet>& ppackets);
    ~ServerRecv(){};
};