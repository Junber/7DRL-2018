#include "object.h"
#include "global.h"

#include <SDL_image.h>
#include <map>

std::deque<Object*> objects, to_delete;

std::map<std::string,SDL_Texture*> loaded_textures;
SDL_Texture* load_image(std::string s)
{
    if (!loaded_textures.count(s)) loaded_textures[s] = IMG_LoadTexture(renderer,(std::string("Data")+PATH_SEPARATOR+"Graphics"+PATH_SEPARATOR+s+".png").c_str());

    return loaded_textures[s];
}

Object::Object(int x, int y, std::string s)
{
    pos[0] = x;
    pos[1] = y;

    killable = false;

    tex = load_image(s);
    SDL_QueryTexture(tex, nullptr, nullptr, &size[0], &size[1]);

    objects.push_back(this);
}

Object::~Object()
{
    remove_it(&objects, this);
}

void Object::render()
{
    SDL_Rect r={pos[0]*tilesize, pos[1]*tilesize, size[0], size[1]};

    SDL_RenderCopy(renderer, tex, nullptr, &r);
}

void Object::attack(Spell* s)
{
    new Object(pos[0],pos[1],"alien_dead");
    to_delete.push_back(this);
}
