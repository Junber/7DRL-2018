#ifndef _GLOBAL
#define _GLOBAL

#if defined(WIN32) || defined(_WIN32)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif

#include <SDL.h>
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

extern SDL_Renderer* renderer;
extern const int window[2],tilesize;
extern const bool grid;

#endif // _GLOBAL
