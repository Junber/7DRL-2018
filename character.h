#ifndef _CHARACTER
#define _CHARACTER

#include "object.h"

class Character: public Object
{
public:
    std::deque<int> moves[2];
    std::deque<Spell*> spells;

    Character(int x, int y, std::string s);
    virtual ~Character();

    void load_spells();
    virtual bool move(int x, int y);
    virtual void attack(Spell* s);
};

#endif // _CHARACTER
