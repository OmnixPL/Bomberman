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

struct ClientSession {
    in6_addr addr;
    std::string name;
    time_t lastActive;

    ClientSession(in6_addr aaddr, std::string nname, time_t last = 0) : addr(aaddr), name(nname), lastActive(last) {};
    inline bool operator==(const ClientSession other) { 
        if (other.addr.__in6_u.__u6_addr32[0] == addr.__in6_u.__u6_addr32[0] &&
            other.addr.__in6_u.__u6_addr32[1] == addr.__in6_u.__u6_addr32[1] &&
            other.addr.__in6_u.__u6_addr32[2] == addr.__in6_u.__u6_addr32[2] &&
            other.addr.__in6_u.__u6_addr32[3] == addr.__in6_u.__u6_addr32[3] &&
            other.name == name) return true; else return false; };
};

class SessionHandler {
    private:
        std::vector<ClientSession>& cs;
        std::string& password;
    public:
        SessionHandler(std::vector<ClientSession>& ccs, std::string& ppassword) : cs(ccs), password(ppassword) {};
        int addNewClient(in6_addr addr, PacketAuth& auth);
        int renewClient(in6_addr addr, Packet& packet);
        int checkTimeouts();
        int removeClient(in6_addr addr, PacketDisconnect& disc);
};

#endif