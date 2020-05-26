#include <stdlib.h> // EXIT_FAILURE

#include "include/server.h"
#include "client.h"
#include "packets.h"



//////////////// special
#include <iostream>
using namespace std;
#include "game.h"

int main(int argc, char *argv[])
{
    // if (argc > 1) {
    //     if (!strcmp(argv[1], "server")) {
    //         Server server(57312);
    //         server.testLoop();
    //         //server.selfTest();
    //     }
    //     else if (argc > 4 && !strcmp(argv[1], "client")) {
    //         Client client(atoi(argv[2]), argv[3], atoi(argv[4]));
    //         client.testLoop();
    //     }
    // }
    // else {
    //     printf("Arguments needed: server OR client IPv4/IPv6 IP_ADDRESS PORT\n");
    //     exit(EXIT_FAILURE);
    // }   
    Game game(2);
    
    // printf("\033c");
    // game.placeBomb(0, {1.4, 0.5});
    // game.placeBomb(0, {5.3, 0.5});
    // game.placeBomb(1, {4.13, 4.01});
    // game.printGamefield();
    // std::cin.get();
    printf("\033c");
    // game.explodeBombsTest();
    game.printGamefield();
    
    char c;
    while(1)
    {
        c = 0;
        std::cin >> c;
        switch(c) {
        case 'w':
            game.updateIntent(0, UP);
            break;
        case 's':
            game.updateIntent(0, DOWN);
            break;
        case 'd':
            game.updateIntent(0, RIGHT);
            break;
        case 'a':
            game.updateIntent(0, LEFT);
            break;
        default:
            cout << endl << "null" << endl;  // not arrow
            break;
        }

        game.updatePlayerPosition(0);
        printf("\033c");
        game.printGamefield();
    }

    return 0;
    
    return 0;
}