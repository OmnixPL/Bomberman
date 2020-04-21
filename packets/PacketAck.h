#include "Packet.h"

class PacketAck : public Packet {
    private:
        int noAck;
    public:
        PacketAck(packet_t type, int no, std::string& user, int noAck);
};