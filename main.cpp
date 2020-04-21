#include <stdlib.h> // EXIT_FAILURE

#include "server.h"
#include "client.h"
#include "packets/packets.h"

int main(int argc, char *argv[])
{
    std::string string = "papiez";
    PacketAck packet(LOBBY, 3, string, 4);
    //Packet packet(ACK, 3, "papiez"); 

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