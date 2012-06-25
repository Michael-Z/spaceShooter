//globals.cpp

#include "SDL/SDL.h"
#include "globals.h"
#include "constants.h"

//The surfaces
SDL_Surface *playerRotated = NULL;
SDL_Surface *player = NULL;

SDL_Surface *background = NULL;
SDL_Surface *screen = NULL;

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

