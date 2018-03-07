#include "character.h"
#include "global.h"

#include <fstream>

Character::Character(int x, int y, std::string s):Object(x, y, s)
{
    killable = true;
    load_spells();
}

void Character::load_spells()
{
    std::fstream file;
    std::string line;

    try
    {
        file.open(std::string("Data")+PATH_SEPARATOR+"Spells"+PATH_SEPARATOR+"spells.txt");
        while (!file.eof())
        {
            std::getline(file,line);
            if (!line.empty()) spells.push_back(new Spell(line));
        }
    }
    catch (...)
    {
        std::cout << "Some spellfile is missing or contains an error or something. What the hell did you do wrong this time, Hisfantor?";
    }
}

bool Character::move(int x, int y)
{
    pos[0] += x;
    pos[1] += y;

    if (pos[0]<0 || pos[0]>=mapsizex || pos[1]<0 || pos[1]>=mapsizey || walls[pos[0]][pos[1]])
    {
        pos[0] -= x;
        pos[1] -= y;

        return false;
    }

    moves[0].push_back(x);
    moves[1].push_back(y);

    for (Spell* s: spells)
    {
        if (s->is_cast(moves)) s->cast(pos[0],pos[1],x,y);
    }

    return true;
}

void Character::attack(Spell* s)
{
    new Object(pos[0],pos[1],"alien_dead");
    to_delete.push_back(this);
}
