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

#include "session.h"
#include "lobby.h"
#include "ServerRecv.h"

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
        std::vector<Packet> packets;

    public:
        Server(int port, std::string password = "");
        int testConnection();
        int selfTest();
        void test2();
        void test3();
};

