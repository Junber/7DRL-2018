#ifndef _PLAYER
#define _PLAYER

#include "character.h"

class Player;
extern Player* player;

class Player: public Character
{
public:
    Player();

    bool move(int x, int y);
    void attack(Spell* s);
};

#endif // _PLAYER
