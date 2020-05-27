#include <stdlib.h> // EXIT_FAILURE

#include "include/server.h"
#include "client.h"
#include "packets.h"

int main(int argc, char *argv[])
{
  if (argc > 2) {
      if (!strcmp(argv[1], "server")) {
          Server server(57312, argv[2]);
          server.start();
      }
    else if (argc > 4 && !strcmp(argv[1], "client")) {
            std::cout<<"argc == "<<argc<<std::endl;
            Client client(
                atoi(argv[2]), 
                argv[3], 
                atoi(argv[4]), 
                argv[5], 
                argv[6], 
                atoi(argv[7]));
            client.runSequential();
        }
    }
    else {
        printf("Arguments needed: server password OR client IPv4/IPv6 IP_ADDRESS PORT USERNAME PATH_TO_MOVES_FILE WAIT_TIME\n");
        exit(EXIT_FAILURE);
    }   
    return 0;
}