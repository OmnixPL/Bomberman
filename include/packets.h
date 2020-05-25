#ifndef PACKETS_H
#define PACKETS_H

#include <string>
#include <vector>

#define NO_BOMBS 2 
#define NO_PLAYERS 4
#define NO_MAP_FIELDS 121
#define MAP_SIDE 11
#define NO_MAP_BYTES 31

// TODO: implement Action, Game

enum packet_t {
    ACK,
    // client to server
    AUTH, RDY, RENEW, DISCONNECT,  // lobby
    ACTION,
    // server to client
    ANS, LOBBY, GAME
};

enum action_t {
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

enum ans_t {OK, BAD_PASSWORD, FULL, TIMEOUT, BAD_USERNAME};

class Packet {
    protected:
        static int noCount;
        packet_t type;
        int no;
        std::string user;
        virtual int deserialize(char* buffer, size_t len);
    public:
        static std::string userDefault;

        Packet(packet_t type, const std::string& user = "");
        Packet(char* buffer, size_t len);

        static packet_t extractType(char* buffer, size_t len);
        
        packet_t getType() { return type; };
        int getNo() { return no; };
        std::string getUser() { return user; };
        
        void setUserDefault(std::string u) { userDefault = u; };
        
        virtual int serialize(char* buffer, size_t len);
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

class PacketGame : public Packet
{
private:
    char mapInfo[NO_MAP_FIELDS];
    int bombPositions[NO_PLAYERS * NO_BOMBS][2];
    float playerPositions[NO_PLAYERS][2];
    bool isPlayerAlive[NO_PLAYERS];

    int serializeMap(char*buffer, size_t len, int offset);
    int serializeBombs(char * buffer, size_t len, int offset);
    int serializePlayerPos(char * buffer, size_t len, int offset);
    int serializePlayerAlive(char * buffer, size_t len, int offset);
public:
    PacketGame(char* buffer, size_t len);
    PacketGame(const std::string user, 
        char map[NO_MAP_FIELDS],
        int bombPos[NO_PLAYERS * NO_BOMBS][2], 
        float playerPos[NO_PLAYERS][2],
        bool isPlayerAlive[NO_PLAYERS]);
    int serialize(char * buffer, size_t len);
    int getBombPositionX(int player, int which);
    int getBombPositionY(int player, int which);
    float getPlayerPosition(int player, int coord);
    bool getPlayerAlive(int player);
    char * getMapInfo();
};


class PacketAction : public Packet
{
private:
    action_t action;
    bool bombPlacement;
public:
    PacketAction(char* buffer, size_t len);
    PacketAction(const std::string user, action_t action, bool bombPlacement);
    int serialize(char* buffer, size_t len);
    action_t getAction();
    bool getBombPlacement();
};




#endif