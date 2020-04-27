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

#define SERV_PORT 57312
#define BUFFERSZ 256

class Server {
    private:
        int servSockfd = -1;
        sockaddr_in6 cliaddr = {}; // maybe change client to sockaddr_storage
        sockaddr_in6 servaddr = {};
        socklen_t len = sizeof(cliaddr);
        std::vector<ClientSession> cs;
        std::string password;
        SessionHandler sh = SessionHandler(cs, password);

    public:
        Server(int port, std::string password = "");
        int testConnection();
        int selfTest();
};

