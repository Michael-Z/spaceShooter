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
SDL_Surface *armor_rep = NULL;

SDL_Surface *levelUpAnimation; //level up animation
SDL_Rect levelUpFrames[16];
int levelUpTimer = 0;

SDL_Surface *mainMessage = NULL;
int mainMessageTimer = 0;

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
SDL_Surface *gameOverBG = NULL;
SDL_Surface *victoryBG = NULL;
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

//victory Button
Button *restartButton = NULL;

//Skill tree buttons
Button *pauseMenuButton = NULL;
Button *offensiveTreeButton = NULL;
Button *defensiveTreeButton = NULL;
Button *abilityTreeButton = NULL;

SDL_Rect skillTreeSelectionFrames[3];

//offensive skill buttons

SkillButton *MS_damageButton = NULL;
SkillButton *MS_rangeButton = NULL;
SkillButton *MS_radiusButton = NULL;
SkillButton *MS_rateButton = NULL;

SkillButton *MG_damageButton = NULL;
SkillButton *MG_speedButton = NULL;
SkillButton *MG_rangeButton = NULL;
SkillButton *MG_doubleButton = NULL;

SkillButton *SG_rangeButton = NULL;
SkillButton *SG_damageButton = NULL;
SkillButton *SG_rateButton = NULL;
SkillButton *SG_doubleButton = NULL;

SkillButton *HM_rangeButton = NULL;
SkillButton *HM_damageButton = NULL;
SkillButton *HM_radiusButton = NULL;
SkillButton *HM_doubleButton = NULL;

//defensive skill buttons

SkillButton *shieldAmountButton;
SkillButton *shieldRegenButton;
SkillButton *shieldCapButton;

SkillButton *armorAmountButton;
SkillButton *hullAmountButton;

SkillButton *evasionButton;
SkillButton *hitRadButton;
SkillButton *damRedButton;

//ability skill buttons
SkillButton *energy_amountButton = NULL;
SkillButton *energy_regenButton = NULL;
SkillButton *shieldRepButton = NULL;
SkillButton *armorRepButton = NULL;
SkillButton *engShieldButton = NULL;
SkillButton *novaRangeButton = NULL;
SkillButton *novaDamageButton = NULL;
SkillButton *EB_costButton = NULL;
SkillButton *EB_damageButton = NULL;


SDL_Surface *skillButtonSelection = NULL;
SDL_Rect skillButtonSelectionFrames[3];

//offensive tree tooltips
SDL_Surface *skillUnavailable = NULL;

//MS
SDL_Surface *MS_damageTTimg = NULL;
SDL_Surface *MS_rangeTTimg = NULL;
SDL_Surface *MS_radiusTTimg = NULL;
SDL_Surface *MS_rateTTimg = NULL;

//MG
SDL_Surface *MG_damageTTimg = NULL;
SDL_Surface *MG_speedTTimg = NULL;
SDL_Surface *MG_rangeTTimg = NULL;
SDL_Surface *MG_doubleTTimg = NULL;

//SG
SDL_Surface *SG_rangeTTimg = NULL;
SDL_Surface *SG_damageTTimg = NULL;
SDL_Surface *SG_rateTTimg = NULL;
SDL_Surface *SG_doubleTTimg = NULL;

//MG
SDL_Surface *HM_rangeTTimg = NULL;
SDL_Surface *HM_damageTTimg = NULL;
SDL_Surface *HM_radiusTTimg = NULL;
SDL_Surface *HM_doubleTTimg = NULL;

//defensive tooltips
SDL_Surface *shield_amountTTimg = NULL;
SDL_Surface *shield_regenTTimg = NULL;
SDL_Surface *shieldCapTTimg = NULL;
SDL_Surface *armor_amountTTimg = NULL;
SDL_Surface *hull_amountTTimg = NULL;
SDL_Surface *evasionTTimg = NULL;
SDL_Surface *hitRadiusTTimg = NULL;
SDL_Surface *damRedTTimg = NULL;

//ability skill tooltips

SDL_Surface *energy_amountTTimg = NULL;
SDL_Surface *energy_regenTTimg = NULL;
SDL_Surface *shieldRepTTimg = NULL;
SDL_Surface *armorRepTTimg = NULL;
SDL_Surface *engShieldTTimg = NULL;
SDL_Surface *novaRangeTTimg = NULL;
SDL_Surface *novaDamageTTimg = NULL;
SDL_Surface *EB_costTTimg = NULL;
SDL_Surface *EB_damageTTimg = NULL;


//explosion clips
SDL_Rect explosion_frames[25];

//shield rep animation
SDL_Rect shield_rep_frames[4];
SDL_Rect armor_rep_frames[4];

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

SDL_Surface *energyBolt = NULL;

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

//game mode
int gameMode = 0;

//current skill tree
int skillTree;

//score of player
Uint32 playerScore;
int playerLevel;

//wave control
int waveCount; //counter used by waves
int waveStage; //for breaking waves into multiple stages
int waveStartFrame; //frame the wave started on
int currentWave;
bool inWave;


bool mute;
bool musicMute;

//Music
Mix_Music *mainMusic = NULL;

//sound effects
Mix_Chunk *moltenSlugSFX = NULL;
Mix_Chunk *miniGunSFX = NULL;
Mix_Chunk *shotgunSFX = NULL;
Mix_Chunk *homingSFX = NULL;

Mix_Chunk *explosionSFX = NULL;
