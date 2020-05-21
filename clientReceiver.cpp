#include "clientReceiver.h"

ClientReceiver::ClientReceiver(int& ccliSockfd, sockaddr_in6& sservaddr) : cliSockfd(ccliSockfd), servaddr(sservaddr) {
    serverLen = sizeof(servaddr);
}

ClientReceiver::~ClientReceiver()
{
}

// void ClientReceiver::defaultBehaviour(char* buffer, size_t len)
// {
//     std::cout<<"I'm inside method defaultBehaviour and I see packet of type "<<Packet::extractType(buffer, len);
//     isExitRequested = true;
// }

std::shared_ptr<Packet> ClientReceiver::grabPacket() {
    char buffer[BUFFERSZ];
    int readCount;
    std::shared_ptr<Packet> packet;

    if ( (readCount = recvfrom(cliSockfd, buffer, BUFFERSZ, MSG_DONTWAIT, (struct sockaddr *) &servaddr, &serverLen)) <= 0) {
        //perror("No packets to read");
        return nullptr;
    }

    packet_t type = Packet::extractType(buffer, BUFFERSZ);
    if ( type == ACK ) {
        packet = std::make_shared<PacketAck>(buffer, readCount);
    }
    else if ( type == ANS ) {
        packet = std::make_shared<PacketAns>(buffer, readCount);
    }
    else if ( type == LOBBY ) {
        packet = std::make_shared<PacketLobby>(buffer, readCount);
    } 
    // TODO add game
    else {
        // TODO ignore?
        packet = std::make_shared<Packet>(buffer, readCount);
    }
    if (!isPacketOK(packet))
        return nullptr;

    return packet;
}

// actually looks like it's really hard to send incorrect packets
// mostly because they either accept all values or have none
bool ClientReceiver::isPacketOK(std::shared_ptr<Packet> packet) {
    int type = packet->getType();

    if ( type == 0)
        return true;
    // accepted packets: ACK, ANS, LOBBY, GAME
    if ( type < 6 || type > 8 )
        return false;

    return true;
}