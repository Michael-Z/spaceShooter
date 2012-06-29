//globals.cpp

#include "SDL/SDL.h"
#include "globals.h"
#include "constants.h"
#include "classes.h"

#include <list>

//The surfaces
//ship surfaces
SDL_Surface *player = NULL;
SDL_Surface *grunt = NULL;

SDL_Surface *explosion = NULL;
SDL_Surface *background = NULL;
SDL_Surface *screen = NULL;

//explosion clips
SDL_Rect explosion_frames[25];

//HUD elements
SDL_Surface *HUD_shield_armor_hull = NULL;
SDL_Rect playerShield;
SDL_Rect playerArmor;
SDL_Rect playerHull;
SDL_Rect playerEnergy;

//surfaces - projectiles
SDL_Surface *moltenSlug = NULL;

//enemy containers
std::list<Grunt*> grunts;

//explosion container
std::list<Explosion*> explosions;

//The event structure
SDL_Event event;

//the Camera
SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

//frame counter
int frame;

//mouse location;
int mouseX;
int mouseY;

