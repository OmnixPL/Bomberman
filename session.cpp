#include "session.h"

int SessionHandler::addNewClient(in6_addr addr, PacketAuth& auth) {
    ClientSession tempcs(addr, auth.getUser(), time(NULL));
    
    if (cs.size() >= 4)
        return -1;  // Max clients already
    
    if (std::find(cs.begin(), cs.end(), tempcs) != cs.end())
        return -2;  // Client already exists

    if (auth.getPassword() != password) {
        std::cout << "Bad password" << std::endl;
        return -3;  // Bad password
    }
        
    cs.push_back(tempcs);

    char ip[80];
    std::cout << "Added new client: " << tempcs.name << " address: " << inet_ntop(AF_INET6, &addr, ip, INET6_ADDRSTRLEN) << " timer: " << tempcs.lastActive << std::endl;
    return 0;
}

int SessionHandler::renewClient(in6_addr addr, Packet& packet) {
    ClientSession tempcs(addr, packet.getUser());
    std::vector<ClientSession>::iterator it; 

    if ( (it = std::find(cs.begin(), cs.end(), tempcs)) == cs.end())
        return -1;  // Client doesn't exist

    it->lastActive = time(NULL);
    std::cout << "Renewed timer of client: " << packet.getUser() << " to: " << it->lastActive << std::endl;
    return 0;
}

int SessionHandler::checkTimeouts() {
    time_t currentTime = time(NULL);

    for (auto it = cs.begin(); it != cs.end();)
    {
        if ((it->lastActive + 10 ) < currentTime) {     // 10 seconds means timeout
            std::cout << "Client timeout" << std::endl;
            it = cs.erase(it);
        }
        else
            ++it;
    } 
    return 0;
}

int SessionHandler::removeClient(in6_addr addr, PacketDisconnect& disc) {
    ClientSession tempcs(addr, disc.getUser());
    std::vector<ClientSession>::iterator it; 

    if ( (it = std::find(cs.begin(), cs.end(), tempcs)) == cs.end())
        return -1;  // Client doesn't exist

    std::cout << "Removing client" << std::endl;
    cs.erase(it);
    return 0;
}