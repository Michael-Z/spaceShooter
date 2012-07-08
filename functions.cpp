#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_rotozoom.h"

#include <iostream>
#include <math.h>
#include <list>

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
    
  //Set the window caption
  SDL_WM_SetCaption("Space Shooter!", NULL );

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
    
  //If everything initialized fine
  return true;
}

bool load_files()
{
  //Load the images
  background = load_image("images/background.png");
  HUD_shield_armor_hull = load_image("images/HUD_shield_armor_hull.png", true);
  explosion = load_image("images/explosion.png", true);
  shield_rep = load_image("images/repairShield_animation.png", true);

  //load ship images
  player = load_image("images/ship.png");
  grunt = load_image("images/grunt.png");
  boomer = load_image("images/boomer.png");
  stealth = load_image("images/stealth.png", true);

  //projectiles
  moltenSlug = load_image("images/moltenSlug.png");
  miniGun = load_image("images/MiniGun.png");
  shotgun = load_image("images/shotgun.png");
  homing = load_image("images/homing.png");

  //If there was a problem in loading the player or background
  if(background == NULL || HUD_shield_armor_hull == NULL ||
     shield_rep == NULL ||
     explosion == NULL ||
     player == NULL || grunt == NULL || boomer == NULL || stealth == NULL ||
     moltenSlug == NULL || miniGun == NULL || shotgun == NULL ||
     homing == NULL)
    {
      printf("failed to load an image\n");
      return false;    
    }
    
  //If everything loaded fine
  return true;
}

void clean_up()
{
  //Free the surface
  SDL_FreeSurface(player);
  SDL_FreeSurface(grunt);
  SDL_FreeSurface(boomer);
  SDL_FreeSurface(stealth);

  SDL_FreeSurface(background);
  SDL_FreeSurface(HUD_shield_armor_hull);

  SDL_FreeSurface(moltenSlug);
  SDL_FreeSurface(miniGun);
  SDL_FreeSurface(shotgun);
  SDL_FreeSurface(homing);
    
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
  apply_surface(0, SCREEN_HEIGHT - 80, HUD_shield_armor_hull, screen);

  //player status bars
  SDL_FillRect(screen, &playerShield, SDL_MapRGB(screen->format, 0, 0xFF,
						 0xFF));

  SDL_FillRect(screen, &playerArmor, SDL_MapRGB(screen->format, 0xA2, 0xA2,
						0xA2));

  SDL_FillRect(screen, &playerHull, SDL_MapRGB(screen->format, 0xFF, 0, 0));
  
  SDL_FillRect(screen, &playerEnergy, SDL_MapRGB(screen->format, 0xFF, 0xFF,
						 0));
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

