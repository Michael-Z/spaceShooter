//globals.cpp

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"

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

//menu backgrounds & buttons
SDL_Surface *mainMenuBG = NULL;
SDL_Surface *mainMenuButtons = NULL;
SDL_Surface *skillTreeSelection = NULL;
SDL_Surface *mainMenuButtonText = NULL;
SDL_Surface *menuBG_1024_768 = NULL;
SDL_Surface *instructionsBG = NULL;
SDL_Surface *pauseMenuBG = NULL;
SDL_Surface *skillTreeBG = NULL;
SDL_Surface *offensiveTreeBG = NULL;
SDL_Surface *defensiveTreeBG = NULL;
SDL_Surface *abilityTreeBG = NULL;

SDL_Surface *mainMenuToolTip = NULL;

Button *mainMenuButton = NULL;

//main menu buttons
Button *startGameButton = NULL;
Button *arcadeModeButton = NULL;
Button *loadGameButton = NULL;
Button *instructionsButton = NULL;
Button *quitGameButton = NULL;

SDL_Rect mainMenuButtonFrames[3];

//pause menu buttons
Button *resumeGameButton = NULL;
Button *skillMenuButton = NULL;
Button *saveGameButton = NULL;

//Skill tree buttons
Button *pauseMenuButton = NULL;
Button *offensiveTreeButton = NULL;
Button *defensiveTreeButton = NULL;
Button *abilityTreeButton = NULL;

SDL_Rect skillTreeSelectionFrames[3];

//offensive skill buttons
Button *MS_damageButton = NULL;
Button *MS_rangeButton = NULL;
Button *MS_radiusButton = NULL;
Button *MS_rateButton = NULL;

SDL_Surface *skillButtonSelection = NULL;
SDL_Rect skillButtonSelectionFrames[3];

//offensive tree tooltips
SDL_Surface *skillUnavailable = NULL;

SDL_Surface *MS_damageTTimg = NULL;
Tooltip *MS_damageTooltip = NULL;

SDL_Surface *MS_rangeTTimg = NULL;
Tooltip *MS_rangeTooltip = NULL;

SDL_Surface *MS_radiusTTimg = NULL;
Tooltip *MS_radiusTooltip = NULL;

SDL_Surface *MS_rateTTimg = NULL;
Tooltip *MS_rateTooltip = NULL;

//explosion clips
SDL_Rect explosion_frames[25];

//shield rep animation
SDL_Rect shield_rep_frames[4];

//ttf font
TTF_Font *font28 = NULL;
SDL_Color font28Color = {255, 255, 255};

TTF_Font *font18 = NULL;
SDL_Color font18Color = {255, 255, 255};

TTF_Font *font14 = NULL;

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

//if the game is paused
bool isPaused = true;

//current menu
int menu = 0;

//current skill tree
int skillTree;

//score of player
Uint32 playerScore;
int playerLevel;

//Music
Mix_Music *mainMusic = NULL;

//sound effects
Mix_Chunk *moltenSlugSFX = NULL;
Mix_Chunk *miniGunSFX = NULL;
Mix_Chunk *shotgunSFX = NULL;
Mix_Chunk *homingSFX = NULL;

Mix_Chunk *explosionSFX = NULL;
