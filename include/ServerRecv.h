#include "packets.h"

class ServerRecv {
    private:
        int& servSockfd;
        std::vector<Packet>& packets;
    public:
        ServerRecv(int& sservSockfd, std::vector<Packet>& ppackets) : servSockfd(sservSockfd), packets(ppackets) {};
        void acceptPackets();
};