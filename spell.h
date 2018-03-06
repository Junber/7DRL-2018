#ifndef _SPELL
#define _SPELL

#include <deque>
#include <string>

void load_spells();

class Spell
{
public:
    std::deque<int> moves[2], effected[2];

    Spell(std::string name);

    bool is_cast(std::deque<int>* moves);
    void cast(int px, int py, int dx, int dy);
};

#endif // _SPELL
