//globals.h

#ifndef GLOBALS_H
#define GLOBALS_H

//The header
#include "SDL/SDL.h"

//The surfaces
extern SDL_Surface *playerRotated;
extern SDL_Surface *player;

extern SDL_Surface *background;
extern SDL_Surface *screen;

//surfaces - projectiles
extern SDL_Surface *moltenSlug;

//The event structure
extern SDL_Event event;

//Camera
extern SDL_Rect camera;

//frame counter
extern int frame;

//mouse location
extern int mouseX;
extern int mouseY;

#endif
