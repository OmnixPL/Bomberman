#include <stdio.h>
#include <stdlib.h> // EXIT_FAILURE
#include <string>
#include <string.h>
#include <unistd.h> // close
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFERSZ 512

class Client {
    private:
        int cliSockfd = -1;
        sockaddr_in6 servaddr = {}, cliaddr = {};
        socklen_t len = sizeof(servaddr);
    public:
        Client(int version, char* addr, int port);
        int test();
};

int client(char *ipVersion, char *addr, char *port);