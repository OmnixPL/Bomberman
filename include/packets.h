#ifndef PACKETS_H
#define PACKETS_H

#include <string>
#include <vector>

// TODO: implement Action, Game

enum packet_t {
    ACK,
    // client to server
    AUTH, RDY, RENEW, DISCONNECT,  // lobby
    ACTION,
    // server to client
    ANS, LOBBY, GAME
};

enum ans_t {OK, BAD_PASSWORD, FULL, TIMEOUT};

class Packet {
    private:
        static int noCount;
        const packet_t type;
        const int no;
        std::string user;
    public:
        static std::string userDefault;
        Packet(packet_t type, const std::string& user = "");
        int getNo() { return no; };
        std::string getUser() { return user; };
        void setUserDefault(std::string u) { userDefault = u; };
};

class PacketAck : public Packet {
    private:
        int noAck;
    public:
        PacketAck(int noAck, const std::string& user = "");
};

class PacketAuth : public Packet {
    private:
        std::string password;
    public:
        PacketAuth(std::string& password, const std::string& user = "");
        std::string getPassword() { return password; };
};

class PacketRdy : public Packet {
    private:
        bool rdy;
    public:
        PacketRdy(bool rdy, const std::string& user = "");
        bool getRdy() { return rdy; };
};

class PacketRenew : public Packet {
    public:
        PacketRenew(const std::string& user = "");
};

class PacketDisconnect : public Packet {
    public:
        PacketDisconnect(const std::string& user = "");
};

class PacketAns : public Packet {
    private:
        ans_t ans;
    public:
        PacketAns(ans_t ans, const std::string& user = "");
};

class PacketLobby : public Packet {
    private:
        std::vector<std::string> players;
        std::vector<bool> rdy;
    public:
        PacketLobby(std::vector<std::string> players, std::vector<bool> rdy, const std::string& user = "");
};

#endif