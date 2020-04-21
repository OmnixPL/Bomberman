#include "Packet.h"
#include <iostream>

Packet::Packet(packet_t ttype, int nno, std::string& uuser) : type(ttype), no(nno), user(uuser) {
    std::cout << "Papież wita " << type << " " << no << " " << user << std::endl ;
}