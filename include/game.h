#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <queue>
#include <chrono>

#include "enums.h"

#define GFIELDSZ 11
#define MAX_PLAYERS 4
#define BOMBS 2

#define TICKS 20 // ticks in second
#define TICKTIME 1000/TICKS // length of tick in milliseconds

#define BLOCKS_PER_SECOND 2.0 // how fast player moves
#define MOVE_PER_TICK BLOCKS_PER_SECOND/TICKS // distance covered per tick

#define SECONDS_TO_EXPLODE 2 // bombs delay

using namespace std::chrono;

// maybe different enum for every player or none or 

class Pos {
    public:
        float x;
        float y;
        Pos(float xx, float yy) : x(xx), y(yy) {}
        Pos() : x(0.0), y(0.0) {}
};

class Player {
    public:
        bool alive;
        int bombsPlaced;
        Pos pos;

        bool walking;
        float toMove;
        action_t direction;
        action_t nextDirection;

        Player() {

            alive = false;
            bombsPlaced = 0;
            walking = false;
            toMove = 0;
            direction = NONE;
            nextDirection = NONE;
        }
};

class Bomb {
    public:
        int x;
        int y;
        time_point<system_clock> time;
        Bomb(int xx, int yy) : x(xx), y(yy) { time = system_clock::now() + seconds(SECONDS_TO_EXPLODE); }
};

class Game {
    private:

        void initGamefield();
        void spawnPlayers();

        void stopPlayer(Player& p);
        void movePlayer(Player& p, float moveValue, action_t direction);
        bool canWalkThere(int x, int y, action_t direction);
    public:
        int playersNo;                    // number of players in game
        Player players[MAX_PLAYERS];


        field_t gamefield[GFIELDSZ][GFIELDSZ];
        std::deque<Bomb> bombs;
        Game(int players);
        void tick();
        bool isInProgress();
        // make those private after finishing testing
        void placeBomb(int player, Pos p);
        void placeBomb(int player);
        void explodeBomb(Bomb b);
        void explodeBombsTest() { while(!bombs.empty()) { explodeBomb(bombs.front()); bombs.pop_front(); } };
        void updateIntent(int pslayer, action_t action);
        void updatePlayerPosition(int player);
        void printGamefield();
};

#endif