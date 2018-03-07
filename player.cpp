#include "player.h"
#include "global.h"
#include "rendering.h"

Player* player;

Player::Player() : Character(mapsizex/2,mapsizey/2,"Protag_idle")
{}

bool Player::move(int x, int y)
{
    if (!Character::move(x,y)) return false;

    for (Object* o: objects) o->update();

    move_camera();

    return true;
}

void Player::attack(Spell* s)
{
    SDL_SetRenderDrawColor(renderer,255,0,0,255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    SDL_Delay(500);
}
