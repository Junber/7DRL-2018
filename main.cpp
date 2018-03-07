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
#include "character.h"
#include "player.h"
#include "rendering.h"

#ifndef _STATIC
void *__gxx_personality_v0;
#endif

const int window[2] = {1000,600};
const int tilesize = 40;
const bool grid = true;

int camera[2] = {0,0};
bool walls[mapsizex][mapsizey];

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

class Random_walker: public Character
{
public:
    Random_walker(int x, int y): Character(x,y,"Cripple Crew Soldier") {}

    void update()
    {
        move(random(-1,1),random(-1,1));
    }
};

SDL_Texture* wall_tex=nullptr;
void gen_wall_tex()
{
    if (!wall_tex)
        wall_tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA4444, SDL_TEXTUREACCESS_TARGET,
                                     mapsizex*tilesize, mapsizey*tilesize);

    SDL_SetRenderTarget(renderer,wall_tex);

    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    for (int i=0;i<mapsizex;i++)
    {
        for (int u=0;u<mapsizey;u++)
        {
            if (walls[i][u])
            {
                SDL_Rect r = {i*tilesize,u*tilesize,tilesize,tilesize};
                SDL_RenderFillRect(renderer,&r);
            }
        }
    }

    SDL_SetRenderTarget(renderer,nullptr);
}

void gen_map()
{
    for (int i=0; i<mapsizex; i++)
    {
        for (int u=0; u<mapsizey; u++)
        {
            walls[i][u] = true;
        }
    }

    int drunk[2] = {mapsizex/2,mapsizey/2};
    int floor = 0;
    while (floor < mapsizex*mapsizey*2/3)
    {
        if (walls[drunk[0]][drunk[1]])
        {
            floor++;
            walls[drunk[0]][drunk[1]] = false;
        }
        drunk[0] = std::max(1, std::min(mapsizex-2, drunk[0]+random(-1,1) ));
        drunk[1] = std::max(1, std::min(mapsizey-2, drunk[1]+random(-1,1) ));
    }

    gen_wall_tex();
}

int main(int argc, char* args[])
{
    IMG_Init(IMG_INIT_PNG);

    renderwindow = SDL_CreateWindow("...", 50, 50, window[0], window[1], SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(renderwindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    gen_map();
    player = new Player();

    move_camera();

    for(int i=0;i<5;i++)
    {
        new Random_walker(random(1,mapsizex),random(1,mapsizey));
    }

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
            if (wall_tex)
            {
                SDL_Rect r = {camera[0]*tilesize,camera[1]*tilesize,window[0],window[1]};
                SDL_RenderCopy(renderer,wall_tex,&r,nullptr);
            }
            else //shouldn't be executed but safety and stuff
            {
                SDL_SetRenderDrawColor(renderer,255,255,255,255);
                SDL_RenderClear(renderer);
            }

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
