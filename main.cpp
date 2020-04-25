#include <stdlib.h> // EXIT_FAILURE

#include "server.h"
#include "client.h"
#include "packets.h"

int main(int argc, char *argv[])
{
    Packet::userDefault = "papiez";

    std::string pass = "okon";
    PacketAuth auth(pass);
    
    PacketAck ack(auth.getNo());
    
    PacketRdy rdy(true);

    PacketAns ans(FULL);

    std::vector<std::string> players = { Packet::userDefault, "Jan", "Paweł", "Karol" };
    std::vector<bool> rdystatus = {0, 0, 0, 1};
    PacketLobby lobby(players, rdystatus);

    if (argc > 1) {
        if (!strcmp(argv[1], "server")) {
            server();
        }
        else if (argc > 4 && !strcmp(argv[1], "client")) {
            client(argv[2], argv[3], argv[4]);
        }
    }
    else {
        printf("Arguments needed: server OR client IPv4/IPv6 IP_ADDRESS PORT\n");
        exit(EXIT_FAILURE);
    }    
    return 0;
}