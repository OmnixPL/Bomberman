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
#include <memory>

#include "clientReceiver.h"
#include "clientSender.h"
#include <model.h>
#include <controller.h>

#define BUFFERSZ 512

class Client {
    private:
        int cliSockfd = -1;
        sockaddr_in6 servaddr = {}, cliaddr = {};
        socklen_t len = sizeof(servaddr); // possibly can be deleted?
        std::mutex queueMutex;
        ClientSender * sender;
        ClientReceiver *  receiver;
        Model * model;
        Controller * controller;
        bool isExitRequested = false;
    public:
        Client(
            int version, 
            char* addr, 
            int port, 
            std::string username, 
            std::string pathToMoves,
            int noSecondsBetweenMoves);
        int test();
        void testSender();
        void testLoop();
        void run();
        void runSequential();
        // void test2();
        // void test3();
        // void test4();
        // void test5();
};

int client(char *ipVersion, char *addr, char *port);