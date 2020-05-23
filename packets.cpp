#include "packets.h"
#include <iostream>
#include <cstring>
#include <stdexcept>      // std::invalid_argument

int Packet::noCount = 0;
std::string Packet::userDefault = "";

Packet::Packet(packet_t ttype, const std::string& uuser) : type(ttype), no(noCount++), user(uuser) {
    if (uuser == "")
        user = userDefault;
    std::cout << "Packet type: " << type << "  number: " << no << "  from: " << user << std::endl ;
}

Packet::Packet(char* buffer, size_t len) {
    deserialize(buffer, len);
}

int Packet::deserialize(char* buffer, size_t len) {
    int offset = 0;

    memcpy(static_cast<packet_t*>(&type), buffer, sizeof(type));
    offset += sizeof(type);
    memcpy(static_cast<int*>(&no), buffer + offset, sizeof(no));
    offset += sizeof(no);
    user = buffer + offset;
    offset += user.size();
    return offset + 1;
}

int Packet::serialize(char* buffer, size_t len) {
    int offset = 0;
    if (len < sizeof(type) + sizeof(no) + user.size() + 1)
        return -1;
    
    memcpy(buffer, &type, sizeof(type));
    offset += sizeof(type);
    memcpy(buffer + offset, &no, sizeof(no));
    offset += sizeof(no);
    user.copy(buffer + offset, user.size());
    offset += user.size();
    buffer[offset] = '\0';
    return offset + 1;
}

packet_t Packet::extractType(char* buffer, size_t len)
{
    if(len < sizeof(type))
    {
        throw std::invalid_argument(std::string("buffer too short"));
    }
    packet_t result;
    memcpy(&result, buffer, sizeof(result));
    return result;
}

PacketAck::PacketAck(int nnoAck, const std::string& user) : Packet{ACK, user}, noAck(nnoAck) {
    std::cout << "  Acknowledged packet no: " << noAck << std::endl;
}

PacketAck::PacketAck(char* buffer, size_t len) : Packet{buffer, len} {
    int offset = sizeof(type) + sizeof(no) + user.size() + 1;
    memcpy(static_cast<int*>(&noAck), buffer + offset, sizeof(noAck));
}

int PacketAck::serialize(char* buffer, size_t len) {
    int offset = Packet::serialize(buffer, len);
    memcpy(buffer + offset, &noAck, sizeof(noAck));
    return 0;
}

PacketAuth::PacketAuth(std::string& ppassword, const std::string& uuser) : Packet{AUTH, uuser}, password(ppassword) {
    std::cout << "  Password: " << password << std::endl;
}

PacketAuth::PacketAuth(char* buffer, size_t len) : Packet{buffer, len} {
    int offset = sizeof(type) + sizeof(no) + user.size() + 1;
    password = buffer + offset;
}

int PacketAuth::serialize(char* buffer, size_t len) {
    int offset = Packet::serialize(buffer, len);
    password.copy(buffer + offset, password.size());
    offset += password.size();
    buffer[offset] = '\0';
    return 0;
}

PacketRdy::PacketRdy(bool rrdy, const std::string& user) : Packet{RDY, user}, rdy(rrdy) {
    std::cout << "  Ready: " << rdy << std::endl;
}

PacketRdy::PacketRdy(char* buffer, size_t len) : Packet{buffer, len} {
    int offset = sizeof(type) + sizeof(no) + user.size() + 1;
    memcpy(static_cast<bool*>(&rdy), buffer + offset, sizeof(rdy));
}

int PacketRdy::serialize(char* buffer, size_t len) {
    int offset = Packet::serialize(buffer, len);
    memcpy(buffer + offset, &rdy, sizeof(rdy));
    return 0;
}

PacketRenew::PacketRenew(const std::string& user) : Packet{RENEW, user} {
    std::cout << "  Renewed" << std::endl;
}

PacketRenew::PacketRenew(char* buffer, size_t len) : Packet{buffer, len}  {}

PacketDisconnect::PacketDisconnect(const std::string& user) : Packet{DISCONNECT, user} {
    std::cout << "  Disconnected" << std::endl;
}

PacketDisconnect::PacketDisconnect(char* buffer, size_t len) : Packet{buffer, len}  {}

PacketAns::PacketAns(ans_t aans, const std::string& user) : Packet{ANS, user}, ans(aans) {
    std::cout << "  Answer: " << ans << std::endl;
}

PacketAns::PacketAns(char* buffer, size_t len) : Packet{buffer, len} {
    int offset = sizeof(type) + sizeof(no) + user.size() + 1;
    memcpy(static_cast<ans_t*>(&ans), buffer + offset, sizeof(ans));
}

int PacketAns::serialize(char* buffer, size_t len) {
    int offset = Packet::serialize(buffer, len);
    memcpy(buffer + offset, &ans, sizeof(ans));
    return 0;
}

PacketLobby::PacketLobby(std::vector<std::string> pplayers, std::vector<bool> rrdy, const std::string& user) : Packet{LOBBY, user}, players(pplayers), rdy(rrdy) {
    for (size_t i = 0; i < pplayers.size(); i++)
        std::cout << "  Player" << i+1 << ": " << players[i] << " rdy: " << rdy[i] << std::endl;
}

PacketLobby::PacketLobby(char* buffer, size_t len) : Packet{buffer, len} {
    int offset = sizeof(type) + sizeof(no) + user.size() + 1;
    uint8_t currentPlayers;
    bool r;
    memcpy(static_cast<uint8_t*>(&currentPlayers), buffer + offset, sizeof(currentPlayers));
    offset += sizeof(currentPlayers);
    for (int i = 0; i < currentPlayers; i++) {
        players.push_back(buffer + offset);
        offset += players[i].size() + 1;
        memcpy(static_cast<bool*>(&r), buffer + offset, sizeof(r));
        rdy.push_back(r);
        offset++;
    }
}

int PacketLobby::serialize(char* buffer, size_t len) {
    int offset = Packet::serialize(buffer, len);
    uint8_t currentPlayers = players.size();
    bool r;
    memcpy(buffer + offset, &currentPlayers, sizeof(currentPlayers));
    offset += sizeof(currentPlayers);
    for (int i = 0; i < currentPlayers; i++) {
        players[i].copy(buffer + offset, players[i].size());
        offset += players[i].size();
        buffer[offset++] = '\0';
        r = rdy[i]; // fix for error: taking address of temporary
        memcpy(buffer + offset, &r, sizeof(rdy[i]));
        offset++;
    }
    return 0;
}

int PacketAction::serialize(char* buffer, size_t len)
{    
    int offset = Packet::serialize(buffer, len);

    memcpy(buffer+offset, &action, sizeof(char));
    offset+=sizeof(char);
    memcpy(buffer+offset, &bombPlacement, sizeof(char));
    offset += sizeof(char);
    return offset;
}

PacketAction::PacketAction(char* buffer, size_t len) : Packet(buffer, len)
{
    int offset = sizeof(type) + sizeof(no) + user.size() + 1;
    action_t actionInBuffer = action_t::NONE;
    bool bombPlacement;
    memcpy(static_cast<action_t*>(&actionInBuffer), buffer + offset,  sizeof(char));
    offset += sizeof(char);
    memcpy(static_cast<bool*>(&bombPlacement), buffer+offset, sizeof(char));
}

PacketAction::PacketAction(const std::string user, action_t action, bool bombPlacement) : Packet(packet_t::ACTION, user), action(action), bombPlacement(bombPlacement){}

PacketGame::PacketGame(const std::string user, 
        char map[NO_MAP_FIELDS],
        int bombPos[NO_PLAYERS][NO_BOMBS], 
        float playerPos[NO_PLAYERS],
        bool playerAlive[NO_PLAYERS]) : 
            Packet(packet_t::GAME, user)
{
    std::copy
    (
        map, 
        map + NO_MAP_FIELDS, 
        mapInfo
    );
    std::copy
    (
        &bombPositions[0][0], 
        &bombPositions[0][0] + NO_PLAYERS * NO_BOMBS,
        &bombPos[0][0]
    );
    std::copy
    (
        playerPos,
        playerPos + NO_PLAYERS,
        playerPositions
    );
    std::cout<<std::endl;
    std::copy
    (
        playerAlive,
        playerAlive + NO_PLAYERS,
        isPlayerAlive
    );
}

PacketGame::PacketGame(char* buffer, size_t len) : 
    Packet(buffer, len)
{
    int offset = sizeof(type) + sizeof(no) + user.size() + 1;

    throw std::runtime_error("Todo implement");
}

int PacketGame::getBombPosition(int player, int which)
{
    return bombPositions[player][which];
}
float PacketGame::getPlayerPosition(int player)
{
    return playerPositions[player];
}
bool PacketGame::getPlayerAlive(int player)
{
    return isPlayerAlive[player];
}

char * PacketGame::getMapInfo()
{
    return mapInfo;
}



int PacketGame::serialize(char * buffer, size_t len)
{
    return -1;
}