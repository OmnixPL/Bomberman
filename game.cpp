#include "include/game.h"

Game::Game(int pplayers) : playersNo(pplayers) {
    initGamefield();
    spawnPlayers();
}

void Game::tick() {
    // move players
    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (players[i].alive == true)
            updatePlayerPosition(i);
    }
    // explode bombs
    while (bombs.front().time < system_clock::now()) {
        explodeBomb(bombs.front());
        bombs.pop_front();
    }
}

bool Game::isInProgress() {
    int alive = 0;
    for (int i = 0; i < playersNo; i++) {
        if (players[i].alive)
            alive++;
    }
    if (alive >= 2)
        return true;
    else return false;
}

void Game::spawnPlayers() {
    // server wont start game without at least 2 players
    players[0].alive = true;
    players[0].pos.x = 0.5;
    players[0].pos.y = 0.5;

    players[1].alive = true;
    players[1].pos.x = GFIELDSZ - 0.5;
    players[1].pos.y = 0.5;

    if (playersNo < 3 )
        return;

    players[2].alive = true;
    players[2].pos.x = 0.5;
    players[2].pos.y = GFIELDSZ - 0.5;

    if (playersNo < 4 )
        return;

    players[3].alive = true;
    players[3].pos.x = GFIELDSZ - 0.5;
    players[3].pos.y = GFIELDSZ - 0.5;
    
}

void Game::initGamefield() {
    for (int y = 0; y < GFIELDSZ; y++) {
        for (int x = 0; x < GFIELDSZ; x++) {
            // if both coords are odd, then place hard wall
            if ( x%2 && y%2 ) {
                gamefield[x][y] = HARD_WALL;
            }
            else {
                gamefield[x][y] = SOFT_WALL;
            }
        }
    }

    // cut out place for players

    // left up corner
    gamefield[0][0] = EMPTY;
    gamefield[0][1] = EMPTY;
    gamefield[1][0] = EMPTY;
    
    // right up corner
    gamefield[GFIELDSZ - 1][0] = EMPTY;
    gamefield[GFIELDSZ - 2][0] = EMPTY;
    gamefield[GFIELDSZ - 1][1] = EMPTY;

    // left down corner
    gamefield[0][GFIELDSZ - 1] = EMPTY;
    gamefield[0][GFIELDSZ - 2] = EMPTY;
    gamefield[1][GFIELDSZ - 1] = EMPTY;

    // right down corner
    gamefield[GFIELDSZ - 1][GFIELDSZ - 1] = EMPTY;
    gamefield[GFIELDSZ - 2][GFIELDSZ - 1] = EMPTY;
    gamefield[GFIELDSZ - 1][GFIELDSZ - 2] = EMPTY;
}

void Game::printGamefield() {
    for (int i = 0; i < MAX_PLAYERS; i++) {
        Player& p = players[i]; 
        std::cout << "Player" << i;
        if (p.alive == true)
            std::cout << " ALIVE";
        else std::cout << " DEAD";
        std::cout << "\tPos: " << p.pos.x << ", " << p.pos.y << std::endl;
        std::cout << "\tD: " << p.direction << " ND: " << p.nextDirection << " ToMove: " << p.toMove << std::endl;
    }
    std::cout << std::endl;
    for (int y = 0; y < GFIELDSZ; y++) {
        for (int x = 0; x < GFIELDSZ; x++) {
            switch ( gamefield[x][y] )
            {
                case EMPTY:
                    std::cout << ".";
                    break;
                case SOFT_WALL:
                    std::cout << "!";
                    break;
                case HARD_WALL:
                    std::cout << "#";
                    break;
                case BOMB:
                    std::cout << "O";
                    break;
                case PLAYER:    // would rather avoid this because can overwrite bomb position
                    std::cout << "+";
                    break;
            }
        }
        std::cout << std::endl;
    }
}

void Game::placeBomb(int player) {
    placeBomb(player, players[player].pos);
}

void Game::placeBomb(int player, Pos p) {
    if ( players[player].bombsPlaced >= 2 )
        return;

    gamefield[(int)p.x][(int)p.y] = BOMB;
    players[player].bombsPlaced++;
    bombs.push_back(Bomb(p.x, p.y));
    return;
}

void Game::explodeBomb(Bomb b) {
    int leftX;
    int rightX;
    int upY;
    int downY;

    gamefield[b.x][b.y] = EMPTY;

    // check walls to destroy (and stop on them)
    for ( leftX = b.x - 1; leftX >= b.x - 3; leftX--) {
        if ( leftX < 0 )
            break;
        if (gamefield[leftX][b.y] == SOFT_WALL) {
            gamefield[leftX][b.y] = EMPTY;
            break;
        }
        if (gamefield[leftX][b.y] == HARD_WALL)
            break;
    }

    for ( rightX = b.x + 1; rightX <= b.x + 3; rightX++) {
        if ( rightX >= GFIELDSZ )
            break;
        if (gamefield[rightX][b.y] == SOFT_WALL) {
            gamefield[rightX][b.y] = EMPTY;
            break;
        }
        if (gamefield[rightX][b.y] == HARD_WALL)
            break;
    }

    for ( downY = b.y + 1; downY <= b.y + 3; downY++) {
        if ( downY >= GFIELDSZ )
            break;
        if (gamefield[b.x][downY] == SOFT_WALL) {
            gamefield[b.x][downY] = EMPTY;
            break;
        }
        if (gamefield[b.x][downY] == HARD_WALL)
            break;
    }

    for ( upY = b.y - 1; upY >= b.y - 3; upY--) {
        if ( upY < 0 )
            break;
        if (gamefield[b.x][upY] == SOFT_WALL) {
            gamefield[b.x][upY] = EMPTY;
            break;
        }
        if (gamefield[b.x][upY] == HARD_WALL)
            break;
    }

    // check for players in explosion radius
    // instead of checking every tile for players, check rectangle --, then | 
    for (int i = 0; i < playersNo; i++) {
        if ( leftX < players[i].pos.x && players[i].pos.x < rightX + 1 )
            if ( b.y < players[i].pos.y && players[i].pos.y < b.y + 1 )
                players[i].alive = false;
    
        if ( upY < players[i].pos.y && players[i].pos.y < downY + 1 )
            if ( b.x < players[i].pos.x && players[i].pos.x < b.x + 1 )
                players[i].alive = false;
    }
}

void Game::updatePlayerPosition(int player) {
    Player& p = players[player];
    float moveValue;

    if (p.walking == false)
        return;

    if (p.toMove > MOVE_PER_TICK) {
        p.toMove -= MOVE_PER_TICK;
        movePlayer(p, MOVE_PER_TICK, p.direction);  // move full distance
    }
    else { 
        moveValue = MOVE_PER_TICK - p.toMove;
        movePlayer(p, p.toMove, p.direction);   // move needed part in this direction and then see next direction
        if (p.nextDirection == NONE) {
            stopPlayer(p);
        }
        else {
            p.toMove = 1 - moveValue;
            p.direction = p.nextDirection;
            p.nextDirection = NONE;
            movePlayer(p, moveValue, p.direction);
        }
    }
}

void Game::stopPlayer(Player& p) {
    p.toMove = 0;
    p.walking = false;
    p.direction = NONE;
    p.nextDirection = NONE;
}

void Game::movePlayer(Player& p, float moveValue, action_t direction) {
    if (direction == LEFT) {
        p.pos.x -= moveValue;
        if (p.pos.x < 0.5) {
            p.pos.x = 0.5;
        }
    }
    else if (direction == RIGHT) {
        p.pos.x += moveValue;
        if (p.pos.x > GFIELDSZ - 0.5) {
            p.pos.x = GFIELDSZ - 0.5;
        }
    }
    else if (direction == UP) {
        p.pos.y -= moveValue;
        if (p.pos.y < 0.5) {
            p.pos.y = 0.5;
        }
    }
    else if (direction == DOWN) {
        p.pos.y += moveValue;
        if (p.pos.y > GFIELDSZ - 0.5) {
            p.pos.y = GFIELDSZ - 0.5;
        }
    }
}

void Game::updateIntent(int player, action_t action) {
    Player& p = players[player];
    int x = p.pos.x;
    int y = p.pos.y;

    // general idea: if stationary, check if can walk in this direction, then go
    // if moving, allow to turn back
    // if moving, allow to turn if past certain threshold
    // really horrible ladder of elses because of minor differences 
    if (action == NONE)
        return;
    if (p.walking == false) {
        if (canWalkThere(x, y, action)) {
            p.walking = true;
            p.toMove = 1;
            p.direction = action;
            p.nextDirection = NONE;
        }
    }
    else {
        if (p.direction == UP || p.direction == DOWN) {
            if (action == p.direction) {    // keep moving

            }
            else if (action == LEFT || action == RIGHT) {   // want to turn
                if (p.toMove < 0.4) {
                    if ( (p.direction == UP && canWalkThere(x, y-1, action)) ||
                         (p.direction == DOWN && canWalkThere(x, y+1, action)) ) {
                            p.nextDirection = action;
                    }                    
                }
            }
            else {  // want to retreat
                if (canWalkThere(x, y, action)) {
                    p.direction = action;
                    p.nextDirection = NONE;
                    p.toMove = 1 - p.toMove;
                }
            }
        }
        else if (p.direction == LEFT || p.direction == RIGHT) {
            if (action == p.direction) {    // keep moving

            }
            else if (action == UP || action == DOWN) {
                if (p.toMove < 0.4) {
                    if ( (p.direction == LEFT && canWalkThere(x-1, y, action)) ||
                         (p.direction == RIGHT && canWalkThere(x+1, y, action)) ) {
                            p.nextDirection = action;
                    }
                }
            }
            else {  // want to retreat
                if (canWalkThere(x, y, action)) {
                    p.direction = action;
                    p.nextDirection = NONE;
                    p.toMove = 1 - p.toMove;
                }
            }
        }
    }
}

bool Game::canWalkThere(int x, int y, action_t direction) {
    if (direction == LEFT) {
        if (x == 0)
            return true;
    }
    else if (direction == RIGHT) {
        if (++x == GFIELDSZ)
            return true;
    }
    else if (direction == UP) {
        if (y == 0)
            return true;
    }
    else if (direction == DOWN) {
        if (++y == GFIELDSZ)
            return true;
    }

    if (gamefield[x][y] == EMPTY)
        return true; 
    else return false;
}