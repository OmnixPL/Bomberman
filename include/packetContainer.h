#ifndef PACKETCONTRAINER_h
#define PACKETCONTRAINER_h

#include <memory>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "packets.h"

class PacketContainer {
    public:
        sockaddr_in6 addr;
        std::shared_ptr<Packet> packet;
        PacketContainer(sockaddr_in6 aaddr, std::shared_ptr<Packet> ppacket) : addr(aaddr), packet(ppacket) {}
};

#endif