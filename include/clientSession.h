#ifndef CLIENTSESSION_H
#define CLIENTSESSION_H

#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>

struct ClientSession {
    in6_addr addr;
    std::string name;
    time_t lastActive;
    bool rdy;

    ClientSession(in6_addr aaddr, std::string nname, time_t last = 0) : addr(aaddr), name(nname), lastActive(last) {};
    inline bool operator==(const ClientSession other) { 
        if (other.addr.__in6_u.__u6_addr32[0] == addr.__in6_u.__u6_addr32[0] &&
            other.addr.__in6_u.__u6_addr32[1] == addr.__in6_u.__u6_addr32[1] &&
            other.addr.__in6_u.__u6_addr32[2] == addr.__in6_u.__u6_addr32[2] &&
            other.addr.__in6_u.__u6_addr32[3] == addr.__in6_u.__u6_addr32[3] &&
            other.name == name) return true; else return false; };
};

#endif