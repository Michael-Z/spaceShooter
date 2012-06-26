//globals.cpp

#include "SDL/SDL.h"
#include "globals.h"
#include "constants.h"
#include "classes.h"

//The surfaces
//ship surfaces
SDL_Surface *player = NULL;
SDL_Surface *grunt = NULL;


SDL_Surface *background = NULL;
SDL_Surface *screen = NULL;

//HUD elements
SDL_Surface *HUD_shield_armor_hull = NULL;
SDL_Rect playerShield;
SDL_Rect playerArmor;
SDL_Rect playerHull;
SDL_Rect playerEnergy;

//surfaces - projectiles
SDL_Surface *moltenSlug = NULL;

//The event structure
SDL_Event event;

//the Camera
SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

//frame counter
int frame;

//mouse location;
int mouseX;
int mouseY;

