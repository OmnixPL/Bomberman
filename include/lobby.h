#include <vector>
#include <session.h>

class Lobby {
    private:
        std::vector<ClientSession>& cs;
    public:
        Lobby(std::vector<ClientSession>& ccs) : cs(ccs) {};
        int clientReady(in6_addr addr, PacketRdy& rdy);
        bool isAllReady();
};