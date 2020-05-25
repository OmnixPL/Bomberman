#include "clientReceiver.h"

ClientReceiver::ClientReceiver(int& ccliSockfd, sockaddr_in6& sservaddr) : 
    Receiver(ccliSockfd, sservaddr)
{
    typeToBehaviour = {
        {packet_t::ANS, handlePacketAns},
        {packet_t::GAME, handlePacketGame},
        {packet_t::LOBBY,handlePacketLobby},
        {packet_t::ACK, handlePacketAck}
    };
}

ClientReceiver::~ClientReceiver()
{
}

std::shared_ptr<Packet> ClientReceiver::grabPacket() {
    char buffer[BUFFERSZ];
    int readCount;
    std::shared_ptr<Packet> packet;

    if ( (readCount = recvfrom(mySockfd, buffer, BUFFERSZ, MSG_DONTWAIT, (struct sockaddr *) &targetAddr, &serverLen)) <= 0) {
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
    else if ( type == GAME )
    {
        packet = std::make_shared<PacketGame>(buffer, readCount);
    }
    else 
    {
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

void ClientReceiver::defaultBehaviour(std::shared_ptr<Packet> packet)
{
    std::cout<<"I'm inside method defaultBehaviour";
    isExitRequested = true;
}

void ClientReceiver::handlePacketAns(std::shared_ptr<Packet> packet)
{
    std::cout<<"ClientReceiver: Handling packet ANS\n";
}
void ClientReceiver::handlePacketLobby(std::shared_ptr<Packet> packet)
{
    std::cout<<"ClientReceiver: Handling packet LOBBY\n";
}
void ClientReceiver::handlePacketGame(std::shared_ptr<Packet> packet)
{
    std::cout<<"ClientReceiver: Handling packet GAME\n";
}
void ClientReceiver::handlePacketAck(std::shared_ptr<Packet> packet)
{
    std::cout<<"ClientReceiver: Handling packet ACK\n";
}