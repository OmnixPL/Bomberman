#ifndef VIEW_H
#define VIEW_H

#include <packets.h>
#include <vector>
#include <iostream>

class LobbyView
{
private:
    std::vector<std::string> players;
    std::vector<bool> playerRdy;
public:
    LobbyView(PacketLobby p);
    friend std::ostream & operator<< (std::ostream &out, const LobbyView &s);
};

class GameView
{
private:
    char fields[MAP_SIDE][MAP_SIDE];
public:
    GameView(PacketGame p);
    friend std::ostream & operator<< (std::ostream &out, const GameView &s);
};

#endif // VIEW_H