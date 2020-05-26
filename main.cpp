#include <stdlib.h> // EXIT_FAILURE

#include "include/server.h"
#include "client.h"
#include "packets.h"



// //////////////// special to test game 
// #include <iostream>
// using namespace std;
// #include "game.h"
// void printPacketGame(PacketGame& g);

int main(int argc, char *argv[])
{
  if (argc > 2) {
      if (!strcmp(argv[1], "server")) {
          Server server(57312, argv[2]);
          server.start();
          //server.testLoop();
          //server.selfTest();
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
            client.testLoop();
        }
    }
    else {
        printf("Arguments needed: server password OR client IPv4/IPv6 IP_ADDRESS PORT USERNAME PATH_TO_MOVES_FILE WAIT_TIME\n");
        exit(EXIT_FAILURE);
    }   
    // Game game(2);
    // game.placeBomb(1, Pos(3.4, 7.0));
    // printf("\033c");
    // game.printGamefield();
    
    // char c;
    // while(1)
    // {
    //     c = 0;
    //     std::cin >> c;
    //     switch(c) {
    //     case 'w':
    //         game.updateIntent(0, UP);
    //         break;
    //     case 's':
    //         game.updateIntent(0, DOWN);
    //         break;
    //     case 'd':
    //         game.updateIntent(0, RIGHT);
    //         break;
    //     case 'a':
    //         game.updateIntent(0, LEFT);
    //         break;
    //     case 'z':
    //         game.placeBomb(0);
    //     default:
    //         cout << endl << "null" << endl;
    //         break;
    //     }

    //     game.updatePlayerPosition(0);
    //     printf("\033c");
    //     PacketGame g(game.gamefield, game.bombs, game.players);

    //     printPacketGame(g);
    //     game.printGamefield();
    // }
    return 0;
}

// void printPacketGame(PacketGame& g) {
//   for (int i = 0; i < MAX_PLAYERS; i++) {
//     std::cout << "Player" << i;
//     if (g.getPlayerAlive(i) == true)
//         std::cout << " ALIVE";
//     else std::cout << " DEAD";
//     std::cout << "\tPos: " << g.getPlayerPosition(i, 0) << ", " << g.getPlayerPosition(i, 1) << std::endl;
//   }
//   for (int i = 0; i < 8; i++) {
//     std::cout << "Bomb" << i << ": (" << g.getBombPositionX(i/2, i%2) << ", " << g.getBombPositionY(i/2, i%2) << ")" << std::endl;
//   }
//   std::cout << std::endl;
//   for (int y = 0; y < GFIELDSZ; y++) {
//     for (int x = 0; x < GFIELDSZ; x++) {
//         switch ( g.getMapInfo()[y*11+x] )
//         {
//             case EMPTY:
//                 std::cout << ".";
//                 break;
//             case SOFT_WALL:
//                 std::cout << "!";
//                 break;
//             case HARD_WALL:
//                 std::cout << "#";
//                 break;
//             case BOMB:
//                 std::cout << "O";
//                 break;
//             case PLAYER:    // would rather avoid this because can overwrite bomb position
//                 std::cout << "+";
//                 break;
//         }
//     }
//     std::cout << std::endl;
//   }
// }