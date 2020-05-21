#include <stdlib.h> // EXIT_FAILURE

#include "include/server.h"
#include "client.h"
#include "packets.h"

int main(int argc, char *argv[])
{
    if (argc > 1) {
        if (!strcmp(argv[1], "server")) {
            Server server(57312);
            server.testLoop();
            //server.selfTest();
        }
        else if (argc > 4 && !strcmp(argv[1], "client")) {
            Client client(atoi(argv[2]), argv[3], atoi(argv[4]));
            client.testLoop();
        }
    }
    else {
        printf("Arguments needed: server OR client IPv4/IPv6 IP_ADDRESS PORT\n");
        exit(EXIT_FAILURE);
    }    
    return 0;
}