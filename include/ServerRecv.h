// Szymon Malolepszy
// Kacper Kula
#include <iostream>
#include <queue>
#include <memory>

#include "packets.h"
#include "receiver.h"
#include "packetContainer.h"
#include "clientSession.h"

#define BUFFERSZ 512

class ServerRecv {
private:
    int& servSockfd;
    std::queue<PacketContainer>& packets;
    std::deque<int>& waitingForAck;
    std::vector<ClientSession>& cs;

    bool isPacketOK(std::shared_ptr<Packet> packet);
public:
    ServerRecv(int& sservSockfd, std::queue<PacketContainer>& packets, std::deque<int>& waitingForAck, std::vector<ClientSession>& cs);
    ~ServerRecv(){};

    int grabPacket();
    int checkoutAck(std::shared_ptr<PacketAck> packet);
};