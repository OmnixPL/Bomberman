// Szymon Malolepszy
// Kacper Kula
#include <stdio.h>
#include <stdlib.h> // EXIT_FAILURE
#include <string.h>
#include <unistd.h> // close
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <vector>
#include <queue>
#include <chrono>
#include <thread>

#include "session.h"
#include "lobby.h"
#include "ServerRecv.h"
#include "serverSender.h"
#include "packetContainer.h"
#include "game.h"

#define SERV_PORT 57312
#define BUFFERSZ 512

class Server {
    private:
        int servSockfd = -1;
        sockaddr_in6 servaddr = {};
        sockaddr_in6 cliaddr = {};
        socklen_t len = sizeof(cliaddr);

        std::vector<ClientSession> cs;
        std::string password;
        
        SessionHandler sh = SessionHandler(cs, password);
        
        Lobby lobby = Lobby(cs);
        
        std::queue<PacketContainer> packets;
        std::deque<int> waitingForAck;  // Packets that need to be acknowledged by client: Ans, Lobby
        ServerRecv receiver = ServerRecv(servSockfd, packets, waitingForAck, cs);
        ServerSender sender = ServerSender(servSockfd, cs);

        void lobbyLoop();
        bool usePacket();
        void gameLoop();
    public:
        Server(int port, std::string password = "");
        void start() { lobbyLoop(); };
};

