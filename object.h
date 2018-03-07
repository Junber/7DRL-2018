#ifndef _OBJECT
#define _OBJECT

#include <deque>
#include <string>
#include <SDL.h>
#include <algorithm>

#include "spell.h"

template<class t> void remove_it(std::deque<t>* base, t thing)
{
    base->erase( std::remove( std::begin(*base), std::end(*base), thing ), std::end(*base) );
}

class Object;
extern std::deque<Object*> objects, to_delete;

class Object
{
public:
    int pos[2], size[2];
    bool killable, dead;
    SDL_Texture* tex;

    Object(int x, int y, std::string s);
    virtual ~Object();

    virtual void update() {};
    virtual void render();
    virtual void attack(Spell* s);
};

#endif // _OBJECT
