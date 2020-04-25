#include "packets.h"
#include <iostream>

int Packet::noCount = 0;
std::string Packet::userDefault = "";

Packet::Packet(packet_t ttype, const std::string& uuser) : type(ttype), no(noCount++) {
    if (uuser == "")
        user = userDefault;
    std::cout << "Packet type: " << type << "  number: " << no << "  from: " << user << std::endl ;
}

PacketAck::PacketAck(int nnoAck, const std::string& user) : Packet{ACK, user}, noAck(nnoAck) {
    std::cout << "  Acknowledged packet no: " << noAck << std::endl;
}

PacketAuth::PacketAuth(std::string& ppassword, const std::string& user) : Packet{AUTH, user}, password(ppassword) {
    std::cout << "  Password: " << password << std::endl;
}

PacketRdy::PacketRdy(bool rrdy, const std::string& user) : Packet{RDY, user}, rdy(rrdy) {
    std::cout << "  Ready: " << rdy << std::endl;
}

PacketRenew::PacketRenew(const std::string& user) : Packet{RENEW, user} {
    std::cout << "  Renewed" << std::endl;
}

PacketDisconnect::PacketDisconnect(const std::string& user) : Packet{DISCONNECT, user} {
    std::cout << "  Disconnected" << std::endl;
}

PacketAns::PacketAns(ans_t aans, const std::string& user) : Packet{ANS, user}, ans(aans) {
    std::cout << "  Answer: " << ans << std::endl;
}

PacketLobby::PacketLobby(std::vector<std::string> pplayers, std::vector<bool> rrdy, const std::string& user) : Packet{LOBBY, user}, players(pplayers), rdy(rrdy) {
    for (int i = 0; i <4; i++) std::cout << "  Player" << i+1 << ": " << players[i] << " rdy: " << rdy[i] << std::endl;
}