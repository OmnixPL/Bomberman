#include "include/ServerRecv.h"
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>
#include <algorithm>

#include "receiver.h"


//ServerRecv::ServerRecv(int& sservSockfd, char* address, int port, struct timeval timeout) : Receiver(sservSockfd, address, port, timeout){}

ServerRecv::ServerRecv(int& sservSockfd, std::queue<PacketContainer>& ppackets, std::deque<int>& wwaitingForAck, std::vector<ClientSession>& ccs) 
    : servSockfd(sservSockfd), packets(ppackets), waitingForAck(wwaitingForAck), cs(ccs) {}

int ServerRecv::grabPacket() {
    char buffer[BUFFERSZ];
    sockaddr_in6 cliaddr = {};
    socklen_t len = sizeof(cliaddr);
    int readCount;
    std::shared_ptr<Packet> packet;
    
    if ( (readCount = recvfrom(servSockfd, buffer, BUFFERSZ, MSG_DONTWAIT, (struct sockaddr *) &cliaddr, &len)) <= 0) {
        //perror("No packets to read");
        return -1;
    }

    packet_t type = Packet::extractType(buffer, BUFFERSZ);
    if ( type == ACK ) {
        packet = std::make_shared<PacketAck>(buffer, readCount);
    }
    else if ( type == AUTH ) {
        packet = std::make_shared<PacketAuth>(buffer, readCount);
    }
    else if ( type == RDY ) {
        packet = std::make_shared<PacketRdy>(buffer, readCount);
    }
    else if ( type == RENEW ) {
        packet = std::make_shared<PacketRenew>(buffer, readCount);
    }
    else if ( type == DISCONNECT ) {
        packet = std::make_shared<PacketDisconnect>(buffer, readCount);
    } 
    else if ( type == ACTION) {
        packet = std::make_shared<PacketAction>(buffer, readCount);
    }
    else {
        return -2;
    }
    if (!isPacketOK(packet))
        return -3;

    PacketContainer packetC(cliaddr, packet);
    packets.push(std::move(packetC));

    return type;
}

// actually looks like it's really hard to send incorrect packets
// mostly because they either accept all values or have none
bool ServerRecv::isPacketOK(std::shared_ptr<Packet> packet) {
    int type = packet->getType();

    // accepted packets: ACK, AUTH, RDY, RENEW, DISCONNECT, ACTION
    if ( type < 0 || type > 5 )
        return false;

    return true;
}

int ServerRecv::checkoutAck(std::shared_ptr<PacketAck> packet) {
    std::deque<int>::iterator it = std::find(waitingForAck.begin(), waitingForAck.end(), packet->getNoAck());
    if ( it != waitingForAck.end() ) {
        waitingForAck.erase(it);
        return 0;
    }
    return -1;
}