#include "clientReceiver.h"
#include <view.h>
#include <thread>

ClientReceiver::ClientReceiver(int& ccliSockfd, sockaddr_in6& sservaddr, bool * exitPointer) : 
    Receiver(ccliSockfd, sservaddr, exitPointer)
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
    *isExitRequested = true;
}

void ClientReceiver::handlePacketAns(std::shared_ptr<Packet> packet)
{
    std::cout<<"ClientReceiver: Handling packet ANS\n";
    std::shared_ptr<PacketAns> packetAns = std::dynamic_pointer_cast<PacketAns>(packet);
    switch (packetAns->getAns())
    {
        case ans_t::OK :
        {
            std::cout<<"Properly connected with server\n";
            break;
        }
        case ans_t::BAD_USERNAME :
        {
            std::cout<<"Username incorrect\n";
            break;
        }
        case ans_t::BAD_PASSWORD :
        {
            std::cout<<"Password incorrect\n";
            break;
        }
        case ans_t::FULL :
        {
            std::cout<<"Lobby is full\n";
            break;
        }
        case ans_t::TIMEOUT :
        {
            std::cout<<"Timeout\n";
            break;
        }    
        default:
            std::cout<<"Packet answer incorrect. Ignored\n";
            break;
    }
}
void ClientReceiver::handlePacketLobby(std::shared_ptr<Packet> packet)
{
    std::cout<<"ClientReceiver: Handling packet Lobby\n";
    std::shared_ptr<PacketLobby> packetLobby = std::dynamic_pointer_cast<PacketLobby>(packet);
    for(size_t i = 0; i < packetLobby->players.size(); i++)
    {
        std::cout<<"Player "<<packetLobby->players[i]<<" "<<(packetLobby->rdy[i] == true ? "READY" : "NOT READY")<<std::endl;;
    }
}
void ClientReceiver::handlePacketGame(std::shared_ptr<Packet> packet)
{
    std::cout<<"ClientReceiver: Handling packet Game no "<<packet->getNo()<<std::endl;
    std::shared_ptr<PacketGame> packetGame = std::dynamic_pointer_cast<PacketGame>(packet);
    GameView view(*packetGame);
    std::cout<<view;
}
void ClientReceiver::handlePacketAck(std::shared_ptr<Packet> packet)
{
    std::cout<<"ClientReceiver: Handling packet ACK\n";
    std::cout<<"Server acknowledged\n";
}