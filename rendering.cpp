#include "rendering.h"
#include "global.h"
#include "player.h"

void move_camera()
{
    if (player->pos[0]-camera[0] < window[0]/3/tilesize)
        camera[0] = std::min(mapsizex-(window[0]/tilesize), std::max(0, player->pos[0]-(window[0]/3/tilesize)));
    else if (player->pos[0]-camera[0] > window[0]*2/3/tilesize)
        camera[0] = std::min(mapsizex-(window[0]/tilesize), std::max(0, player->pos[0]-(window[0]*2/3/tilesize)));

    if (player->pos[1]-camera[1] < window[1]/3/tilesize)
        camera[1] = std::min(mapsizey-(window[1]/tilesize), std::max(0, player->pos[1]-(window[1]/3/tilesize)));
    else if (player->pos[1]-camera[1] > window[1]*2/3/tilesize)
        camera[1] = std::min(mapsizey-(window[1]/tilesize), std::max(0, player->pos[1]-(window[1]*2/3/tilesize)));
}
