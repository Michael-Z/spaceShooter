//globals.h

#ifndef GLOBALS_H
#define GLOBALS_H

//The header
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"

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

//menu backgrounds & buttons
extern SDL_Surface *mainMenuBG;
extern SDL_Surface *mainMenuButtons;
extern SDL_Surface *skillTreeSelection;
extern SDL_Surface *mainMenuButtonText;
extern SDL_Surface *menuBG_1024_768;

extern SDL_Surface *instructionsBG;
extern SDL_Surface *pauseMenuBG;
extern SDL_Surface *skillTreeBG;
extern SDL_Surface *offensiveTreeBG;
extern SDL_Surface *defensiveTreeBG;
extern SDL_Surface *abilityTreeBG;

extern SDL_Surface *mainMenuToolTip;

extern Button *mainMenuButton;

//main menu buttons
extern Button *startGameButton;
extern Button *arcadeModeButton;
extern Button *loadGameButton;
extern Button *instructionsButton;
extern Button *quitGameButton;

extern SDL_Rect mainMenuButtonFrames[3];

//pause menu buttons
extern Button *resumeGameButton;
extern Button *skillMenuButton;
extern Button *saveGameButton;

//Skill tree Buttons
extern Button *pauseMenuButton;
extern Button *offensiveTreeButton;
extern Button *defensiveTreeButton;
extern Button *abilityTreeButton;

extern SDL_Rect skillTreeSelectionFrames[3];

//offensive skill buttons
extern Button *MS_damageButton;
extern Button *MS_rangeButton;
extern Button *MS_radiusButton;
extern Button *MS_rateButton;

extern SDL_Surface *skillButtonSelection;
extern SDL_Rect skillButtonSelectionFrames[3];

//offensive tree tooltips
extern SDL_Surface *skillUnavailable;

extern SDL_Surface *MS_damageTTimg;
extern Tooltip *MS_damageTooltip;

extern SDL_Surface *MS_rangeTTimg;
extern Tooltip *MS_rangeTooltip;

extern SDL_Surface *MS_radiusTTimg;
extern Tooltip *MS_radiusTooltip;

extern SDL_Surface *MS_rateTTimg;
extern Tooltip *MS_rateTooltip;

//explosion_clips
extern SDL_Rect explosion_frames[25];

//shield rep animation
extern SDL_Rect shield_rep_frames[4];

//ttf font
extern TTF_Font *font28;
extern SDL_Color font28Color;

extern TTF_Font *font18;
extern SDL_Color font18Color;

extern TTF_Font *font14;

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

//if game is paused
extern bool isPaused;

//current menu
extern int menu;

//current skill tree
extern int skillTree;

//player score
extern Uint32 playerScore;
extern int playerLevel;

//sound effects

extern Mix_Music *mainMusic;
extern Mix_Chunk *moltenSlugSFX;
extern Mix_Chunk *miniGunSFX;
extern Mix_Chunk *shotgunSFX;
extern Mix_Chunk *homingSFX;

extern Mix_Chunk *explosionSFX;

#endif
