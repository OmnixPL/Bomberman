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
    protected:
        static int noCount;
        packet_t type;
        int no;
        std::string user;
        int deserialize(char* buffer, size_t len);
    public:
        static std::string userDefault;

        Packet(packet_t type, const std::string& user = "");
        Packet(char* buffer, size_t len);
        
        packet_t getType() { return type; };
        int getNo() { return no; };
        std::string getUser() { return user; };
        
        void setUserDefault(std::string u) { userDefault = u; };
        
        int serialize(char* buffer, size_t len);
};

class PacketAck : public Packet {
    private:
        int noAck;
    public:
        PacketAck(int noAck, const std::string& user = "");
        PacketAck(char* buffer, size_t len);

        int getNoAck() { return noAck; };

        int serialize(char* buffer, size_t len);
};

class PacketAuth : public Packet {
    private:
        std::string password;
    public:
        PacketAuth(std::string& password, const std::string& user = "");
        PacketAuth(char* buffer, size_t len);
        std::string getPassword() { return password; };
        
        int serialize(char* buffer, size_t len);
};

class PacketRdy : public Packet {
    private:
        bool rdy;
    public:
        PacketRdy(bool rdy, const std::string& user = "");
        PacketRdy(char* buffer, size_t len);
        bool getRdy() { return rdy; };
        
        int serialize(char* buffer, size_t len);
};

class PacketRenew : public Packet {
    public:
        PacketRenew(const std::string& user = "");
        PacketRenew(char* buffer, size_t len);
};

class PacketDisconnect : public Packet {
    public:
        PacketDisconnect(const std::string& user = "");
        PacketDisconnect(char* buffer, size_t len);
};

class PacketAns : public Packet {
    private:
        ans_t ans;
    public:
        PacketAns(ans_t ans, const std::string& user = "");
        PacketAns(char* buffer, size_t len);
        
        ans_t getAns() { return ans; };

        int serialize(char* buffer, size_t len);
};

class PacketLobby : public Packet {
    private:
    public:
        std::vector<std::string> players;
        std::vector<bool> rdy;
        PacketLobby(std::vector<std::string> players, std::vector<bool> rdy, const std::string& user = "");
        PacketLobby(char* buffer, size_t len);
        
        int serialize(char* buffer, size_t len);
};

#endif