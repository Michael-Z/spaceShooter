//globals.h

#ifndef GLOBALS_H
#define GLOBALS_H

//The header
#include "SDL/SDL.h"

#include "classes.h"

#include <list>


//The surfaces
extern SDL_Surface *player;
extern SDL_Surface *grunt;

extern SDL_Surface *explosion;
extern SDL_Surface *background;
extern SDL_Surface *screen;

//HUD elements
extern SDL_Surface *HUD_shield_armor_hull;
extern SDL_Rect playerShield;
extern SDL_Rect playerArmor;
extern SDL_Rect playerHull;
extern SDL_Rect playerEnergy;

//surfaces - projectiles
extern SDL_Surface *moltenSlug;

//enemy containers
extern std::list<Grunt*> grunts;

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
