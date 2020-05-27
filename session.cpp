// Szymon Malolepszy
// Kacper Kula
#include "session.h"

ans_t SessionHandler::addNewClient(sockaddr_in6 addr, PacketAuth& auth) {
    ClientSession tempcs(addr, auth.getUser(), time(NULL));
    tempcs.rdy = false;
    
    if (cs.size() >= 4)
        return FULL;  // Max clients already
    
    if (std::find(cs.begin(), cs.end(), tempcs) != cs.end())
        return BAD_USERNAME;  // Client already exists

    if (auth.getPassword() != password) {
        std::cout << "Bad password" << std::endl;
        return BAD_PASSWORD;  // Bad password
    }

    if (auth.getUser().size() > 15)
        return BAD_USERNAME;  // username too long
        
    cs.push_back(tempcs);

    char ip[80];
    std::cout << "Added new client: " << tempcs.name << " address: " << inet_ntop(AF_INET6, &addr.sin6_addr, ip, INET6_ADDRSTRLEN) << " timer: " << tempcs.lastActive << std::endl;
    return OK;
}

int SessionHandler::renewClient(sockaddr_in6 addr, Packet& packet) {
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

int SessionHandler::removeClient(sockaddr_in6 addr, PacketDisconnect& disc) {
    ClientSession tempcs(addr, disc.getUser());
    std::vector<ClientSession>::iterator it; 

    if ( (it = std::find(cs.begin(), cs.end(), tempcs)) == cs.end())
        return -1;  // Client doesn't exist

    std::cout << "Removing client: " << disc.getUser() << std::endl;
    cs.erase(it);
    return 0;
}