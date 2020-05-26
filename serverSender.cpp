#include "include/serverSender.h"

ServerSender::ServerSender(int& sservSockfd, std::vector<ClientSession>& ccs) : servSockfd(sservSockfd), cs(ccs) {}

int ServerSender::sendAck(ClientSession client, int noAck) {
    socklen_t clientLen = sizeof(client.addr);
    char buffer[BUFFERSZ];
    PacketAck ack(noAck);

    ack.serialize(buffer, BUFFERSZ);
    if ( sendto(servSockfd, buffer, sizeof(ack), 0, (const struct sockaddr *) &(client.addr), clientLen) < 0 )
        return -1;

    return 0;
}

int ServerSender::sendAck(sockaddr_in6 client, int noAck) {
    socklen_t clientLen = sizeof(client);
    char buffer[BUFFERSZ];
    PacketAck ack(noAck);

    ack.serialize(buffer, BUFFERSZ);
    if ( sendto(servSockfd, buffer, sizeof(ack), 0, (const struct sockaddr *) &(client), clientLen) < 0 )
        return -1;

    return 0;
}

int ServerSender::sendAns(sockaddr_in6 client, ans_t ans) {
    socklen_t clientLen = sizeof(client);
    char buffer[BUFFERSZ];
    PacketAns packet(ans);

    packet.serialize(buffer, BUFFERSZ);
    if ( sendto(servSockfd, buffer, sizeof(packet), 0, (const struct sockaddr *) &(client), clientLen) < 0 )
        return -1;

    return 0;
}

int ServerSender::sendLobby(ClientSession client) {
    socklen_t clientLen = sizeof(client);
    char buffer[BUFFERSZ];

    std::vector<std::string> players;
    std::vector<bool> ready;

    for (ClientSession client : cs) {
        players.push_back(client.name);
        ready.push_back(client.rdy);
    }

    PacketLobby rdy(players, ready);

    rdy.serialize(buffer, BUFFERSZ);
    if ( sendto(servSockfd, buffer, sizeof(rdy), 0, (const struct sockaddr *) &(client), clientLen) < 0 )
        return -1;

    return 0;
}

int ServerSender::sendLobbyAll() {
    for (ClientSession client : cs) {
        if ( sendLobby(client) < 0 )
            return -1;
    }
    return 0;
}

int ServerSender::sendGame(ClientSession client) {
    socklen_t clientLen = sizeof(client);
    char buffer[BUFFERSZ];

    PacketGame g(game.gamefield, game.bombs, game.players);

    g.serialize(buffer, BUFFERSZ);
    if ( sendto(servSockfd, buffer, sizeof(g), 0, (const struct sockaddr *) &(client), clientLen) < 0 )
        return -1;

    return 0;
}

int ServerSender::sendGameAll() {
    for (ClientSession client : cs) {
        if ( sendGame(client) < 0 )
            return -1;
    }
    return 0;
}