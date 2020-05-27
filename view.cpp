#include <view.h>

std::ostream & operator<<(std::ostream &out, const GameView &s)
{
    out<<"Game map looks as follows:\n";
    for(int i = 0; i < MAP_SIDE; i++)
    {
        for(int j = 0; j < MAP_SIDE; j++)
        {
            out<<s.fields[i][j]<<" ";
        }
        out<<"\n\n";
    }
    return out;
}

GameView::GameView(PacketGame p)
{
    char * map = p.getMapInfo();
    for(int i = 0; i < NO_MAP_FIELDS; i++)
    {
        char result;
        switch ((int)map[i])
        {
            case 0:
            {
                result = ' ';
                break;
            }
            case 1:
            {
                result = '#';
                break;
            }
            case 2:
            {
                result = '$';
                break;
            }
            case 3:
            {
                result = 'x';
                break;
            }
            default:
                break;
        }
        fields[i/MAP_SIDE][i % MAP_SIDE] = result;
    }

    for (size_t i = 0; i < NO_PLAYERS; i++)
    {
        int x = p.getBombPositionX(i, 0);
        int y = p.getBombPositionY(i, 0);
        if(x < MAP_SIDE && y < MAP_SIDE)
        {
            fields[x][y] = '*';
        }
        x = p.getBombPositionX(i, 1);
        y = p.getBombPositionY(i, 1);
        if(x < MAP_SIDE && y < MAP_SIDE)
        {
            fields[x][y] = '*';
        }
    }

    for(int i = 0; i < NO_PLAYERS; i++ )
    {
        if(p.getPlayerAlive(i))
        {
            int x = p.getPlayerPosition(i, 0);
            int y = p.getPlayerPosition(i, 1);
            fields[x][y] = '0' + i;
        }
    }
}