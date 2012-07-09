//globals.h

#ifndef GLOBALS_H
#define GLOBALS_H

//The header
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

#include "classes.h"

#include <list>


//The surfaces
extern SDL_Surface *player;
extern SDL_Surface *grunt;
extern SDL_Surface *boomer;
extern SDL_Surface *stealth;
extern SDL_Surface *carrier;

extern SDL_Surface *explosion;
extern SDL_Surface *shield_rep;

extern SDL_Surface *mainMessage;
extern int mainMessageTimer; //timer for main message

extern SDL_Surface *scoreHUD;
extern SDL_Surface *levelHUD;


extern SDL_Surface *background;
extern SDL_Surface *screen;

//explosion_clips
extern SDL_Rect explosion_frames[25];

//shield rep animation
extern SDL_Rect shield_rep_frames[4];

//ttf font
extern TTF_Font *font28;
extern SDL_Color font28Color;

//HUD elements
extern SDL_Surface *HUD_shield_armor_hull;
extern SDL_Rect playerShield;
extern SDL_Rect playerArmor;
extern SDL_Rect playerHull;
extern SDL_Rect playerEnergy;
extern SDL_Rect playerExp;

//surfaces - projectiles
extern SDL_Surface *moltenSlug;
extern SDL_Surface *miniGun;
extern SDL_Surface *shotgun;
extern SDL_Surface *homing;

//enemy containers
extern std::list<Grunt*> grunts;
extern std::list<Boomer*> boomers;
extern std::list<Stealth*> stealths;
extern std::list<Carrier*> carriers;

//explosion containers
extern std::list<Explosion*> explosions;

//The event structure
extern SDL_Event event;

//Camera
extern SDL_Rect camera;

//frame counter
extern int frame;

//mouse location
extern int mouseX;
extern int mouseY;

//player score
extern Uint32 playerScore;
extern int playerLevel;

#endif
