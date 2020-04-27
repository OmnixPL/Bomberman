#include "lobby.h"

int Lobby::clientReady(in6_addr addr, PacketRdy& rdy) {
    ClientSession tempcs(addr, rdy.getUser());
    std::vector<ClientSession>::iterator it; 

    if ( (it = std::find(cs.begin(), cs.end(), tempcs)) == cs.end())
        return -1;  // Client doesn't exist

    it->rdy = rdy.getRdy();
    return 0;
}

bool Lobby::isAllReady() {
    if (cs.size() == 0)
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