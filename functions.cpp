#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_rotozoom.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"

#include <iostream>
#include <math.h>
#include <list>
#include <sstream>

#include "classes.h"
#include "constants.h"
#include "functions.h"
#include "globals.h"

int distForm(int x1, int y1, int x2, int y2)
{
  return int(sqrt(double(pow(x1 - x2, 2)) + pow(y1 - y2, 2)));
}

double unitToAngle(double x1, double y1)
{
  if(y1 < 0)
      return acos(x1);

  else
      return 2 * PI - acos(x1);
}

double angleToUnitX(double angle)
{
  return cos(angle);
}

double angleToUnitY(double angle)
{
  //negative because y is reversed
  return -sin(angle);
}

SDL_Surface *load_image(const char* filename, bool transparent = false)
{
  //The image that's loaded
  SDL_Surface* loadedImage = NULL;
    
  //The optimized surface that will be used
  SDL_Surface* optimizedImage = NULL;
    
  //Load the image
  loadedImage = IMG_Load(filename);
    
  //If the image loaded
  if( loadedImage != NULL )
    {

      //Create an optimized surface
      if(transparent)
	optimizedImage = SDL_DisplayFormatAlpha(loadedImage);
      else
	optimizedImage = SDL_DisplayFormat( loadedImage );
        
      //Free the old surface
      SDL_FreeSurface( loadedImage );
        
      //If the surface was optimized
      if( optimizedImage != NULL )
        {
	  //Color key surface
	  SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY,
			  SDL_MapRGB(optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }
    
  //Return the optimized surface
  return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip )
{
  //Holds offsets
  SDL_Rect offset;
    
  //Get offsets
  offset.x = x;
  offset.y = y;
    
  //Blit
  SDL_BlitSurface(source, clip, destination, &offset);
}

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
  if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
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

  //If there was a problem in loading the player or background
  if(background == NULL || HUD_shield_armor_hull == NULL ||
     shield_rep == NULL ||
     explosion == NULL ||
     player == NULL || grunt == NULL || boomer == NULL || stealth == NULL ||
     carrier == NULL || 
     moltenSlug == NULL || miniGun == NULL || shotgun == NULL ||
     homing == NULL ||
     mainMenuBG == NULL || mainMenuButtons == NULL ||
     mainMenuButtonText == NULL || menuBG_1024_768 == NULL ||
     instructionsBG == NULL || pauseMenuBG == NULL || skillTreeBG == NULL ||
     skillTreeSelection == NULL || offensiveTreeBG == NULL ||
     defensiveTreeBG == NULL || abilityTreeBG == NULL)
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

  //set main menu clips
  for(int i = 0; i < 1; i++) //one button for now
    {
      for(int j = 0; j < 3; j++)
	{
	  int mmBF = 3 *i + j;
	  mainMenuButtonFrames[mmBF].x = j * 300;
	  mainMenuButtonFrames[mmBF].y = i * 100;
	  mainMenuButtonFrames[mmBF].w = 300;
	  mainMenuButtonFrames[mmBF].h = 100;
	}
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

void clean_up()
{
  //Free the surface
  SDL_FreeSurface(player);
  SDL_FreeSurface(grunt);
  SDL_FreeSurface(boomer);
  SDL_FreeSurface(stealth);
  SDL_FreeSurface(carrier);

  SDL_FreeSurface(background);
  SDL_FreeSurface(HUD_shield_armor_hull);

  SDL_FreeSurface(moltenSlug);
  SDL_FreeSurface(miniGun);
  SDL_FreeSurface(shotgun);
  SDL_FreeSurface(homing);

  SDL_FreeSurface(mainMenuBG);
  SDL_FreeSurface(mainMenuButtons);
  SDL_FreeSurface(mainMenuButtonText);

  SDL_FreeSurface(instructionsBG);
  SDL_FreeSurface(pauseMenuBG);
  SDL_FreeSurface(skillTreeBG);
  SDL_FreeSurface(skillTreeSelection);
  SDL_FreeSurface(offensiveTreeBG);
  SDL_FreeSurface(defensiveTreeBG);
  SDL_FreeSurface(abilityTreeBG);

  //free sound effecs
  Mix_FreeChunk(moltenSlugSFX);
  Mix_FreeChunk(miniGunSFX);
  Mix_FreeChunk(shotgunSFX);
  Mix_FreeChunk(homingSFX);
  Mix_FreeChunk(explosionSFX);
  
  Mix_FreeMusic(mainMusic);
  
  //close font
  TTF_CloseFont(font28);
  TTF_CloseFont(font18);

  //quit sdl_mixer
  Mix_CloseAudio();

  //quit SDL_ttf
  TTF_Quit();
  
    
  //Quit SDL
  SDL_Quit();
}

//rotate image
SDL_Surface* rotate(SDL_Surface* source, double angle, double zoom,
		    int smooth)
{
  SDL_Surface* rotatefile = NULL;
  SDL_Surface* optimizedrotate = NULL;

  rotatefile = rotozoomSurface(source, angle, zoom, smooth);
  optimizedrotate = SDL_DisplayFormat(rotatefile);

  SDL_FreeSurface(rotatefile);

  return optimizedrotate;
    
}

void renderHUD()
{
  //player status bars background
  apply_surface(0, SCREEN_HEIGHT - 90, HUD_shield_armor_hull, screen);

  //player status bars
  SDL_FillRect(screen, &playerShield, SDL_MapRGB(screen->format, 0, 0xFF,
						 0xFF));

  SDL_FillRect(screen, &playerArmor, SDL_MapRGB(screen->format, 0xA2, 0xA2,
						0xA2));

  SDL_FillRect(screen, &playerHull, SDL_MapRGB(screen->format, 0xFF, 0, 0));
  
  SDL_FillRect(screen, &playerEnergy, SDL_MapRGB(screen->format, 0xFF, 0xFF,
						 0));

  SDL_FillRect(screen, &playerExp, SDL_MapRGB(screen->format, 0, 0x46, 0xd5));

  /*
  //render health bar numbers
  SDL_Surface *shieldSurface = TTF_RenderText_Solid(font14, pShieldNum,
						    font28Color);
  
  SDL_Surface *armorSurface = TTF_RenderText_Solid(font14, pArmorNum,
						   font28Color);
  
  SDL_Surface *hullSurface = TTF_RenderText_Solid(font14, pHullNum,
						  font28Color);

  SDL_Surface *energySurface = TTF_RenderText_Solid(font14, pEnergyNum,
						    font28Color);

  //198 is middle of status bars
  apply_surface(198 - shieldSurface->w, SCREEN_HEIGHT - 78, shieldSurface,
		screen);

  apply_surface(198 - armorSurface->w, SCREEN_HEIGHT - 58, armorSurface,
		screen);

  apply_surface(198 - hullSurface->w, SCREEN_HEIGHT - 38, hullSurface,
		screen);

  apply_surface(198 - energySurface->w, SCREEN_HEIGHT - 18, energySurface,
		screen);
  */

  //render main Message
  if(mainMessageTimer > 0)
    {
      mainMessageTimer--;
      apply_surface(int(SCREEN_WIDTH * 3.5 / 8), int(SCREEN_HEIGHT / 4),
		    mainMessage, screen);
    }

  //render score
  std::stringstream scoreStr;

  scoreStr << "Score: " << playerScore;

  scoreHUD = TTF_RenderText_Solid(font18, scoreStr.str().c_str(), font18Color);

  apply_surface(5, 0, scoreHUD, screen);

  //here for later implementation

  std::stringstream levelStr;

  levelStr << "Level: " << playerLevel;
  levelHUD = TTF_RenderText_Solid(font18, levelStr.str().c_str(), font18Color);

  apply_surface(5, 18, levelHUD, screen);
}

void handle_menu_input()
{
  if(event.type == SDL_MOUSEMOTION)
    {
      mouseX = event.motion.x;
      mouseY = event.motion.y;
    }
}


void doGrunts()
{
  for(std::list<Grunt*>::iterator it = grunts.begin(); it != grunts.end();)
    {

      if((*it)->getHull() == 0)
	{
	  delete * it;
	  grunts.erase(it++);
	}
      else
	{

	  //(**it).doUnit(grunts, it);
	  (**it).doUnit(it);
	  ++it;
	}
    }
}

void doBoomers()
{
  for(std::list<Boomer*>::iterator it = boomers.begin(); it != boomers.end();)
    {
      if((*it)->getHull() == 0)
	{
	  delete * it;
	  boomers.erase(it++);
	}
      else
	{

	  (**it).doUnit();
	  ++it;
	}
    }
}

void doStealths()
{
  for(std::list<Stealth*>::iterator it = stealths.begin();
      it != stealths.end();)
    {
      if((*it)->getHull() == 0)
	{
	  delete *it;
	  stealths.erase(it++);
	}
      else
	{
	  (*it)->doUnit(it);
	  it++;
	}
    }
}

void doCarriers()
{
  for(std::list<Carrier*>::iterator it = carriers.begin();
      it != carriers.end();)
    {
      if((*it)->getHull() == 0)
	{
	  (**it).die();
	  delete *it;
	  carriers.erase(it++);
	}
      else
	{
	  (*it)->doUnit(it);
	  it++;
	}
    }
}

void doExplosions()
{
  for(std::list<Explosion*>::iterator it = explosions.begin();
      it != explosions.end();)
    {
      if((**it).get_stage() == 24)
	{
	  delete *it;
	  explosions.erase(it++);
	}
      else
	{
	(**it).show();
	++it;
	}
    }
}

void gameOver()
{
  std::cout << "Game Over!\n";
}

