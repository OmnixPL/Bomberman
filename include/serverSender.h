#include <vector>
#include "clientSession.h"
#include "packets.h"

#define BUFFERSZ 512

class ServerSender {
private:
    int& servSockfd;
    std::vector<ClientSession>& cs;

public:
    ServerSender(int& sservSockfd, std::vector<ClientSession>& cs);
    ~ServerSender(){};

    int sendAck(ClientSession client, int noAck);
    int sendAck(sockaddr_in6 client, int noAck);
    int sendAns(sockaddr_in6 client, ans_t ans);
    int sendLobby(ClientSession client);
    int sendLobbyAll();
    int sendGame(ClientSession client, Game& game);
    int sendGameAll(Game& game);
};