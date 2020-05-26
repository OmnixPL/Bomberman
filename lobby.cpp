#include "lobby.h"

int Lobby::clientReady(sockaddr_in6 addr, PacketRdy& rdy) {
    ClientSession tempcs(addr, rdy.getUser());
    std::vector<ClientSession>::iterator it; 

    if ( (it = std::find(cs.begin(), cs.end(), tempcs)) == cs.end())
        return -1;  // Client doesn't exist

    it->rdy = rdy.getRdy();
    std::cout << "Client: " << rdy.getUser() << " is ready: " << rdy.getRdy() << std::endl;
    return 0;
}

bool Lobby::isAllReady() {
    if (cs.size() < 2)
        return false;

    for (auto tempcs : cs) {
        if (!(tempcs.rdy)) {
            std::cout << "Not everyone is ready" << std::endl;
            return false;
        }
    }
    std::cout << "Everyone is ready" << std::endl;
    return true;
}

int Lobby::unreadyAll() {
    for (unsigned int i = 0; i < cs.size(); i++) {
        cs[i].rdy = false;
    }
    return 0;
}