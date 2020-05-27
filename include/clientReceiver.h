// Szymon Malolepszy
// Kacper Kula
#ifndef CLIENT_RECEIVER_H
#define CLIENT_RECEIVER_H

#include <memory>
#include "receiver.h"

#define BUFFERSZ 512

class ClientReceiver : public Receiver 
{
private:

    bool isPacketOK(std::shared_ptr<Packet> packet);
    void defaultBehaviour(std::shared_ptr<Packet> packet);
    static void handlePacketAns(std::shared_ptr<Packet> packet);
    static void handlePacketAck(std::shared_ptr<Packet> packet);
    static void handlePacketLobby(std::shared_ptr<Packet> packet);
    static void handlePacketGame(std::shared_ptr<Packet> packet);
public:
    // ClientReceiver(int& cliSockfd, char* address, int port, struct timeval timeout);
    ClientReceiver(int& ccliSockfd, sockaddr_in6& sservaddr, bool * exitPointer);
    ~ClientReceiver();

    std::shared_ptr<Packet> grabPacket();   // currently returns packet but can be easily added to queue if needed
};


#endif