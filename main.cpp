#include <stdlib.h> // EXIT_FAILURE

#include "include/server.h"
#include "client.h"
#include "packets.h"

int main(int argc, char *argv[])
{
    Packet::userDefault = "papiez";
    std::string pls = "pls";
    std::string pass = "okon";
    PacketAuth auth(pass, pls);
    //PacketAuth auth2(pass, pass);
    
    PacketAck ack(auth.getNo(), pls);
    
    PacketRdy rdy(true, pls);

    PacketAns ans(FULL);

    std::vector<std::string> players = { Packet::userDefault, "Jan", "Paweł", "Karol" };
    std::vector<bool> rdystatus = {0, 0, 0, 1};
    PacketLobby lobby(players, rdystatus);

    if (argc > 1) {
        if (!strcmp(argv[1], "server")) {
            Server server(57312);
            server.testConnection();
            //server.selfTest();
        }
        else if (argc > 4 && !strcmp(argv[1], "client")) {
            Client client(atoi(argv[2]), argv[3], atoi(argv[4]));
            client.test();
        }
    }
    else {
        printf("Arguments needed: server OR client IPv4/IPv6 IP_ADDRESS PORT\n");
        exit(EXIT_FAILURE);
    }    
    return 0;
}