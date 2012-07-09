//globals.cpp

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

#include "globals.h"
#include "constants.h"
#include "classes.h"

#include <list>

//The surfaces
//ship surfaces
SDL_Surface *player = NULL;
SDL_Surface *grunt = NULL;
SDL_Surface *boomer = NULL;
SDL_Surface *stealth = NULL;
SDL_Surface *carrier = NULL;

SDL_Surface *explosion = NULL;
SDL_Surface *shield_rep = NULL;

SDL_Surface *mainMessage = NULL;
int mainMessageTimer = 0;

SDL_Surface *scoreHUD = NULL;
SDL_Surface *levelHUD = NULL;

SDL_Surface *background = NULL;
SDL_Surface *screen = NULL;

//explosion clips
SDL_Rect explosion_frames[25];

//shield rep animation
SDL_Rect shield_rep_frames[4];

//ttf font
TTF_Font *font28 = NULL;
SDL_Color font28Color = {255, 255, 255};

//HUD elements
SDL_Surface *HUD_shield_armor_hull = NULL;
SDL_Rect playerShield;
SDL_Rect playerArmor;
SDL_Rect playerHull;
SDL_Rect playerEnergy;
SDL_Rect playerExp;

//surfaces - projectiles
SDL_Surface *moltenSlug = NULL;
SDL_Surface *miniGun = NULL;
SDL_Surface *shotgun = NULL;
SDL_Surface *homing = NULL;

//enemy containers
std::list<Grunt*> grunts;
std::list<Boomer*> boomers;
std::list<Stealth*> stealths;
std::list<Carrier*> carriers;

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

//score of player
Uint32 playerScore;
int playerLevel;

