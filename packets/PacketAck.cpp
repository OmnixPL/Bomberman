#include <iostream>
#include "PacketAck.h"

PacketAck::PacketAck(packet_t type, int no, std::string& user, int nnoAck) : Packet{type, no, user}, noAck(nnoAck) {
    std::cout << "JESZCZE JACK" << std::endl;
}