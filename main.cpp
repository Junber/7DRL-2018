#include <SDL.h>
#include <SDL_image.h>
#include <deque>
#include <map>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <random>
#include <time.h>

#include "spell.h"
#include "global.h"
#include "object.h"

#ifndef _STATIC
void *__gxx_personality_v0;
#endif

const int window[2] = {500,500};
const int tilesize = 50;
const bool grid = true;

bool breakk = false;
SDL_Window* renderwindow;
SDL_Renderer* renderer;

int last_time;
float wait;
void limit_fps()
{
    wait = (100.0/6)-(SDL_GetTicks() - last_time);
    if (wait>0) SDL_Delay(wait);
    last_time = SDL_GetTicks();
}

std::default_random_engine generator;
int random(int x, int y)
{
    std::uniform_int_distribution<int> distribution(x,y);
    return distribution(generator);
}

void random_init()
{
    generator.seed(time(nullptr));
    random(0,1);
}

class Character: public Object
{
public:
    std::deque<int> moves[2];
    std::deque<Spell*> spells;

    Character(int x, int y, std::string s):Object(x, y, s)
    {
        killable = true;
        load_spells();
    }

    void load_spells()
    {
        std::fstream file;
        std::string line;

        file.open(std::string("Data")+PATH_SEPARATOR+"Spells"+PATH_SEPARATOR+"spells.txt");
        while (!file.eof())
        {
            std::getline(file,line);
            if (!line.empty()) spells.push_back(new Spell(line));
        }
    }

    virtual void move(int x, int y)
    {
        pos[0] += x;
        pos[1] += y;

        moves[0].push_back(x);
        moves[1].push_back(y);

        for (Spell* s: spells)
        {
            if (s->is_cast(moves)) s->cast(pos[0],pos[1],x,y);
        }
    }
};

class Random_walker: public Character
{
public:
    Random_walker(int x, int y): Character(x,y,"Cripple Crew Soldier") {}

    void update()
    {
        move(random(-1,1),random(-1,1));
    }
};

class Player: public Character
{
public:
    Player():Character(0,0,"Protag_idle")
    {
    }

    void move(int x, int y)
    {
        Character::move(x,y);
        for (Object* o: objects) o->update();
    }
};

int main(int argc, char* args[])
{
    IMG_Init(IMG_INIT_PNG);

    renderwindow = SDL_CreateWindow("...", 50, 50, window[0], window[1], SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(renderwindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    Player* player = new Player();

    for(int i=0;i<5;i++) new Random_walker(random(1,7),random(1,7));

    //SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_BLEND);
    SDL_Event e;
	while (!breakk)
    {
        while(SDL_PollEvent(&e))
        {
			if (e.type == SDL_QUIT) breakk = true;

			else if (e.type == SDL_KEYDOWN)
			{
			    switch (e.key.keysym.sym)
			    {
                case SDLK_ESCAPE:
                    breakk = true;
                    break;
                case SDLK_KP_1:
                case SDLK_b:
                    player->move(-1,1);
                    break;
                case SDLK_KP_2:
                case SDLK_j:
                    player->move(0,1);
                    break;
                case SDLK_KP_3:
                case SDLK_n:
                    player->move(1,1);
                    break;
                case SDLK_KP_4:
                case SDLK_h:
                    player->move(-1,0);
                    break;
                case SDLK_KP_5:
                case SDLK_PERIOD:
                    player->move(0,0);
                    break;
                case SDLK_KP_6:
                case SDLK_l:
                    player->move(1,0);
                    break;
                case SDLK_KP_7:
                case SDLK_y:
                case SDLK_z:
                    player->move(-1,-1);
                    break;
                case SDLK_KP_8:
                case SDLK_k:
                    player->move(0,-1);
                    break;
                case SDLK_KP_9:
                case SDLK_u:
                    player->move(1,-1);
                    break;
			    }
			}
        }

        for (Object* o: to_delete) delete o;
        to_delete.clear();

        { //Rendering
            SDL_SetRenderDrawColor(renderer,255,255,255,255);
            SDL_RenderClear(renderer);

            if (grid)
            {
                SDL_SetRenderDrawColor(renderer,0,0,0,255);

                for (int x=0;x<window[0];x+=tilesize)
                {
                    SDL_RenderDrawLine(renderer,x,0,x,window[1]);
                }

                for (int y=0;y<window[1];y+=tilesize)
                {
                    SDL_RenderDrawLine(renderer,0,y,window[0],y);
                }
            }

            for (Object* o: objects) o->render();
        }

        SDL_RenderPresent(renderer);
        limit_fps();
    }

    return 0;
}
