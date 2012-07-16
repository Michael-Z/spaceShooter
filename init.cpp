//init.cpp

#include "globals.h"
#include "functions.h"
#include "constants.h"

bool init()
{
  //Initialize all SDL subsystems
  if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
      return false;    
    }
    
  //Set up the screen
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP,
			    SDL_SWSURFACE);
    
  //If there was in error in setting up the screen
  if( screen == NULL )
    {
      return false;    
    }

  if( TTF_Init() == -1)
    {
      return false;
    }

  //initialize SDL_mixer
  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
      return false;
    }
    
  //Set the window caption
  SDL_WM_SetCaption("Star Arena", NULL );



  //set default skill tree and menu
  menu = 0;
  skillTree = 0;
    
  //If everything initialized fine
  return true;
}

bool load_files()
{
  //load ttf font
  font28 = TTF_OpenFont("FreeSans.ttf", 28);
  font18 = TTF_OpenFont("FreeSans.ttf", 18);
  font14 = TTF_OpenFont("FreeSans.ttf", 14);

  //Load the images
  background = load_image("images/background.png");
  HUD_shield_armor_hull = load_image("images/HUD_shield_armor_hull.png", true);
  explosion = load_image("images/explosion.png", true);
  shield_rep = load_image("images/repairShield_animation.png", true);
  skillTreeSelection = load_image("images/skillTreeSelectionFrames.png", true);
  levelUpAnimation = load_image("images/levelUpAnimation.png", true);

  //load ship images
  player = load_image("images/ship.png");
  grunt = load_image("images/grunt.png");
  boomer = load_image("images/boomer.png");
  stealth = load_image("images/stealth.png", true);
  carrier = load_image("images/carrier.png");

  //projectiles
  moltenSlug = load_image("images/moltenSlug.png");
  miniGun = load_image("images/MiniGun.png");
  shotgun = load_image("images/shotgun.png");
  homing = load_image("images/homing.png");

  //menu items
  
  menuBG_1024_768 = load_image("images/menuBG_1024-768.png");
  mainMenuBG = load_image("images/mainMenuBG.png", true);
  mainMenuButtons = load_image("images/mainMenuButtons.png", true);
  mainMenuButtonText = load_image("images/mainMenuButtonText.png", true);

  instructionsBG = load_image("images/instructionsBG.png", true);
  pauseMenuBG = load_image("images/pauseMenuBG.png", true);
  skillTreeBG = load_image("images/skillTreeBG.png", true);
  offensiveTreeBG = load_image("images/offensiveSkills.png", true);
  defensiveTreeBG = load_image("images/defensiveSkills.png", true);
  abilityTreeBG = load_image("images/abilitySkills.png", true);

  skillButtonSelection = load_image("images/skillButtonSelection.png", true);
  skillUnavailable = load_image("images/skillUnavailable.png", true);

  //tooltips
  MS_damageTTimg = load_image("images/MS_damageTTimg.png", true);
  MS_rangeTTimg = load_image("images/MS_rangeTTimg.png", true);
  MS_radiusTTimg = load_image("images/MS_radiusTTimg.png", true);
  MS_rateTTimg = load_image("images/MS_rateTTimg.png", true);

  MG_damageTTimg = load_image("images/MG_damageTTimg.png", true);
  MG_speedTTimg = load_image("images/MG_speedTTimg.png", true);
  MG_rangeTTimg = load_image("images/MG_rangeTTimg.png", true);
  MG_doubleTTimg = load_image("images/MG_doubleTTimg.png", true);

  //If there was a problem in loading the player or background
  if(background == NULL || HUD_shield_armor_hull == NULL ||
     shield_rep == NULL ||
     explosion == NULL || levelUpAnimation == NULL ||
     player == NULL || grunt == NULL || boomer == NULL || stealth == NULL ||
     carrier == NULL || 
     moltenSlug == NULL || miniGun == NULL || shotgun == NULL ||
     homing == NULL ||
     mainMenuBG == NULL || mainMenuButtons == NULL ||
     mainMenuButtonText == NULL || menuBG_1024_768 == NULL ||
     instructionsBG == NULL || pauseMenuBG == NULL || skillTreeBG == NULL ||
     skillTreeSelection == NULL || offensiveTreeBG == NULL ||
     defensiveTreeBG == NULL || abilityTreeBG == NULL ||
     skillButtonSelection == NULL || skillUnavailable == NULL ||
     MS_damageTTimg == NULL || MS_rangeTTimg == NULL ||
     MS_radiusTTimg == NULL || MS_rateTTimg == NULL ||
     MG_damageTTimg == NULL || MG_speedTTimg == NULL ||
     MG_rangeTTimg == NULL || MG_doubleTTimg == NULL)
    {
      printf("failed to load an image\n");
      return false;    
    }

  if(font28 == NULL || font18 == NULL)
    {
      printf("failed to load ttf font");
      return false;
    }

  //load sounds
  mainMusic = Mix_LoadMUS("sounds/mainMusic.wav");
  if(mainMusic == NULL)
    {
      printf("failed to load Music\n");
      return false;
    }
  
  moltenSlugSFX = Mix_LoadWAV("sounds/moltenSlugSFX.wav");
  miniGunSFX = Mix_LoadWAV("sounds/miniGunSFX.wav");
  shotgunSFX = Mix_LoadWAV("sounds/shotgunSFX.wav");
  homingSFX = Mix_LoadWAV("sounds/homingSFX.wav");

  explosionSFX = Mix_LoadWAV("sounds/explosionSFX.wav");

  if(moltenSlugSFX == NULL || miniGunSFX == NULL || shotgunSFX == NULL ||
     homingSFX == NULL || explosionSFX == NULL)
    {
      printf("failed to load sound effects");
      return false;
    }
    
  //If everything loaded fine
  return true;
}

void setButtons_and_Frames()
{
  //set status bar bounds
  //status bar start x = 98, bar height = 15, bar width = 200;

  playerShield.x = 98;
  playerShield.y = SCREEN_HEIGHT - 78;
  playerShield.h = 17;
  playerShield.w = 200;

  playerArmor.x = 98;
  playerArmor.y = SCREEN_HEIGHT - 58;
  playerArmor.h = 17;
  playerArmor.w = 200;

  playerHull.x = 98;
  playerHull.y = SCREEN_HEIGHT - 38;
  playerHull.h = 17;
  playerHull.w = 200;

  playerEnergy.x = 98;
  playerEnergy.y = SCREEN_HEIGHT - 18;
  playerEnergy.h = 17;
  playerEnergy.w = 200;

  playerExp.x = 0;
  playerExp.y = SCREEN_HEIGHT - 89;
  playerExp.h = 8;
  playerExp.w = 0;

  //level up animation clips
  for(int i = 0; i < 16; i++)
    {
      levelUpFrames[i].x = (i % 4) * 100;
      levelUpFrames[i].y = (i / 4) * 100;
      levelUpFrames[i].h = 100;
      levelUpFrames[i].w = 100;
    }

  //set main menu clips
  for(int j = 0; j < 3; j++)
    {
      int mmBF = j;
      mainMenuButtonFrames[mmBF].x = j * 300;
      mainMenuButtonFrames[mmBF].y = 0;
      mainMenuButtonFrames[mmBF].w = 300;
      mainMenuButtonFrames[mmBF].h = 100;
    }

  //create buttons
  //main Menu Buttons
  startGameButton = new Button(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 4,
			       300, 100,
			       mainMenuButtons,
			       &mainMenuButtonFrames[0],
			       &mainMenuButtonFrames[1],
			       &mainMenuButtonFrames[2]);

  arcadeModeButton = new Button(SCREEN_WIDTH / 2 - 150,
				SCREEN_HEIGHT / 4 + 110,
				300, 100, mainMenuButtons,
				&mainMenuButtonFrames[0],
				&mainMenuButtonFrames[1],
				&mainMenuButtonFrames[2]);

  loadGameButton = new Button(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 4 + 220,
			      300, 100, mainMenuButtons,
			      &mainMenuButtonFrames[0],
			      &mainMenuButtonFrames[1],
			      &mainMenuButtonFrames[2]);

  instructionsButton = new Button(SCREEN_WIDTH / 2 - 150,
				  SCREEN_HEIGHT / 4 + 330,
				  300, 100, mainMenuButtons,
				  &mainMenuButtonFrames[0],
				  &mainMenuButtonFrames[1],
				  &mainMenuButtonFrames[2]);

  quitGameButton = new Button(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 4 + 440,
			      300, 100, mainMenuButtons,
			      &mainMenuButtonFrames[0],
			      &mainMenuButtonFrames[1],
			      &mainMenuButtonFrames[2]);

  mainMenuButton = new Button(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT - 130,
			      300, 100, mainMenuButtons,
			      &mainMenuButtonFrames[0],
			      &mainMenuButtonFrames[1],
			      &mainMenuButtonFrames[2]);

  //pause menu buttons
  resumeGameButton = new Button(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 4,
				300, 100, mainMenuButtons,
				&mainMenuButtonFrames[0],
				&mainMenuButtonFrames[1],
				&mainMenuButtonFrames[2]);

  skillMenuButton = new Button(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 4 + 110,
			       300, 100, mainMenuButtons,
			       &mainMenuButtonFrames[0],
			       &mainMenuButtonFrames[1],
			       &mainMenuButtonFrames[2]);

  saveGameButton = new Button(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 4 + 220,
			      300, 100, mainMenuButtons,
			      &mainMenuButtonFrames[0],
			      &mainMenuButtonFrames[1],
			      &mainMenuButtonFrames[2]);

  //set skillTreeSelection clips
  for(int i = 0; i < 3; i++)
    {
      skillTreeSelectionFrames[i].x = 150 * i;
      skillTreeSelectionFrames[i].y = 0;
      skillTreeSelectionFrames[i].w = 150;
      skillTreeSelectionFrames[i].h = 150;
    }

  pauseMenuButton = new Button(SCREEN_WIDTH - 200, 0, 150, 150,
			       skillTreeSelection,
			       &skillTreeSelectionFrames[0],
			       &skillTreeSelectionFrames[1],
			       &skillTreeSelectionFrames[2]);
  
  offensiveTreeButton = new Button(SCREEN_WIDTH - 200, 200, 150, 150,
				   skillTreeSelection,
				   &skillTreeSelectionFrames[0],
				   &skillTreeSelectionFrames[1],
				   &skillTreeSelectionFrames[2]);
  
  defensiveTreeButton = new Button(SCREEN_WIDTH - 200, 350, 150, 150,
				   skillTreeSelection,
				   &skillTreeSelectionFrames[0],
				   &skillTreeSelectionFrames[1],
				   &skillTreeSelectionFrames[2]);
  
  abilityTreeButton = new Button(SCREEN_WIDTH - 200, 500, 150, 150,
				 skillTreeSelection,
				 &skillTreeSelectionFrames[0],
				 &skillTreeSelectionFrames[1],
				 &skillTreeSelectionFrames[2]);

  //set skill button selection frames
  for(int i = 0; i < 3; i++)
    {
      skillButtonSelectionFrames[i].x = i * 140;
      skillButtonSelectionFrames[i].y = 0;
      skillButtonSelectionFrames[i].w = 140;
      skillButtonSelectionFrames[i].h = 140;
    }

  //offensive skill buttons
  MS_damageButton = new SkillButton(30, 160, 140, 140, MS_damageTTimg);
  MS_rangeButton = new SkillButton(30, 300, 140, 140, MS_rangeTTimg);
  MS_radiusButton = new SkillButton(30, 440, 140, 140, MS_radiusTTimg);
  MS_rateButton = new SkillButton(30, 580, 140, 140, MS_rateTTimg);

  MG_damageButton = new SkillButton(190, 160, 140, 140, MG_damageTTimg);
  MG_speedButton = new SkillButton(190, 300, 140, 140, MG_speedTTimg);
  MG_rangeButton = new SkillButton(190, 440, 140, 140, MG_rangeTTimg);
  MG_doubleButton = new SkillButton(190, 580, 140, 140, MG_doubleTTimg);
  
  
  //set explosion frame clips
  for(int i = 0; i < 25; i++)
    {
      explosion_frames[i].x = 64 * (i % 5);
      explosion_frames[i].y = 64 * (i / 5);
      explosion_frames[i].w = 64;
      explosion_frames[i].h = 64;
    }

  //set shield_rep frame clips
  for(int i = 0; i < 4; i++)
    {
      shield_rep_frames[i].x = 60 * (i % 2);
      shield_rep_frames[i].y = 60 * (i / 2);
      shield_rep_frames[i].w = 60;
      shield_rep_frames[i].h = 60;
    }
}

void create_Tooltips()
{
  void();
}
