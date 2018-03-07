#ifndef _GLOBAL
#define _GLOBAL

#if defined(WIN32) || defined(_WIN32)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif

#include <SDL.h>
#include <iostream> //Remove for release

#define mapsizex 50
#define mapsizey 50

extern SDL_Renderer* renderer;
extern const int window[2],tilesize;
extern const bool grid;

extern int camera[2];
extern bool walls[mapsizex][mapsizey];

#endif // _GLOBAL
