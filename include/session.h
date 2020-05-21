#ifndef SESSION_H
#define SESSION_H

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <stdlib.h> // EXIT_FAILURE
#include <string.h>
#include <unistd.h> // close
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctime>

#include "packets.h"
#include "clientSession.h"

class SessionHandler {
    private:
        std::vector<ClientSession>& cs;
        std::string& password;
    public:
        SessionHandler(std::vector<ClientSession>& ccs, std::string& ppassword) : cs(ccs), password(ppassword) {};
        ans_t addNewClient(sockaddr_in6 addr, PacketAuth& auth);
        int renewClient(sockaddr_in6 addr, Packet& packet);
        int checkTimeouts();
        int removeClient(sockaddr_in6 addr, PacketDisconnect& disc);
};

#endif