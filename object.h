#ifndef _OBJECT
#define _OBJECT

#include <deque>
#include <string>
#include <SDL.h>
#include <algorithm>

template<class t> void remove_it(std::deque<t>* base, t thing)
{
    base->erase( std::remove( std::begin(*base), std::end(*base), thing ), std::end(*base) );
}

class Object;
extern std::deque<Object*> objects;

class Object
{
public:
    int pos[2], size[2];
    SDL_Texture* tex;

    Object(int x, int y, std::string s);
    virtual ~Object();

    virtual void update() {};
    virtual void render();
};

#endif // _OBJECT
