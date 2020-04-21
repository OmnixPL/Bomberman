#ifndef PACKET_H
#define PACKET_H

#include <string>

enum packet_t {
    ACK,
    // client to server
    CONNECT_ASK, AUTH, READY, RENEW, DISCONNECT,  // lobby
    ACTION,
    // server to client
    CONNECT_ANS, TIMEOUT, LOBBY, GAME
};

class Packet {
    private:
        packet_t type;
        int no;
        std::string user;
    public:
        Packet(packet_t type, int no, std::string& user);

};

#endif