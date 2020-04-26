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

#include "packets.h"

struct ClientSession {
    in6_addr addr;
    std::string name;
    ClientSession(in6_addr aaddr, std::string nname) : addr(aaddr), name(nname) {};
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
    public:
        SessionHandler(std::vector<ClientSession>& ccs) : cs(ccs) {};
        int addNewClient(in6_addr addr, PacketAuth& auth);
};

int SessionHandler::addNewClient(in6_addr addr, PacketAuth& auth) {
    ClientSession tempcs(addr, auth.getUser());
    
    if (cs.size() >= 4)
        return -1;
    
    if (std::find(cs.begin(), cs.end(), tempcs) != cs.end())
        return -2;

    cs.push_back(tempcs);
    std::cout << "Added new client: " << tempcs.name << std::endl;
    return 0;
}

#endif