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

SDL_Surface *load_image(const char* filename, bool transparent)
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
  SDL_FreeSurface(explosion);
  SDL_FreeSurface(levelUpAnimation);

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

  SDL_FreeSurface(skillButtonSelection);
  SDL_FreeSurface(skillUnavailable);

  SDL_FreeSurface(MS_damageTTimg);
  SDL_FreeSurface(MS_rangeTTimg);
  SDL_FreeSurface(MS_radiusTTimg);
  SDL_FreeSurface(MS_rateTTimg);

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
  TTF_CloseFont(font14);

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

void renderHUD(Player *player)
{
  //player status bars background
  apply_surface(0, SCREEN_HEIGHT - 90, HUD_shield_armor_hull, screen);

  //player status bars
  SDL_FillRect(screen, &playerShield, SDL_MapRGB(screen->format, 0, 0xFF,
						 0xFF));

  SDL_FillRect(screen, &playerArmor, SDL_MapRGB(screen->format, 0xA2, 0xA2,
						0xA2));

  SDL_FillRect(screen, &playerHull, SDL_MapRGB(screen->format, 0xFF, 0, 0));
  
  SDL_FillRect(screen, &playerEnergy, SDL_MapRGB(screen->format, 0x88, 0,
						 0x88));

  SDL_FillRect(screen, &playerExp, SDL_MapRGB(screen->format, 0, 0x46, 0xd5));

  //render bar numbers
  std::stringstream shieldNum;
  std::stringstream armorNum;
  std::stringstream hullNum;
  std::stringstream energyNum;

  shieldNum << player->getShield() << " / " << player->getMaxShield();
  armorNum << player->getArmor() << " / " << player->getMaxArmor();
  hullNum << player->getHull() << " / " << player->getMaxHull();
  energyNum << player->getEnergy() << " / " << player->getMaxEnergy();

  SDL_Color color = { 0xFF, 0xFF, 0xFF };

  SDL_Surface *shieldSurface = TTF_RenderText_Solid(font14,
						    shieldNum.str().c_str(),
						    color);
  
  SDL_Surface *armorSurface = TTF_RenderText_Solid(font14,
						   armorNum.str().c_str(),
						   color);
  
  SDL_Surface *hullSurface = TTF_RenderText_Solid(font14,
						  hullNum.str().c_str(),
						  color);

  SDL_Surface *energySurface = TTF_RenderText_Solid(font14,
						    energyNum.str().c_str(),
						    color);
  //198 is middle of status bars
  apply_surface(198 - shieldSurface->w / 2, SCREEN_HEIGHT - 78, shieldSurface,
		screen);

  apply_surface(198 - armorSurface->w / 2, SCREEN_HEIGHT - 58, armorSurface,
		screen);

  apply_surface(198 - hullSurface->w / 2, SCREEN_HEIGHT - 38, hullSurface,
		screen);

  apply_surface(198 - energySurface->w / 2, SCREEN_HEIGHT - 18, energySurface,
		screen);

  //free surfaces
  SDL_FreeSurface(shieldSurface);
  SDL_FreeSurface(armorSurface);
  SDL_FreeSurface(hullSurface);
  SDL_FreeSurface(energySurface);
  //*/

  //render main Message
  if(mainMessageTimer > 0)
    {
      mainMessageTimer--;
      apply_surface((SCREEN_WIDTH - mainMessage->w) / 2,int(SCREEN_HEIGHT / 4),
		    mainMessage, screen);
      if(mainMessageTimer == 0)
	SDL_FreeSurface(mainMessage);
    }

  //render score
  std::stringstream scoreStr;

  scoreStr << "Score: " << playerScore;

  scoreHUD = TTF_RenderText_Solid(font18, scoreStr.str().c_str(), font18Color);

  apply_surface(5, 0, scoreHUD, screen);

  SDL_FreeSurface(scoreHUD);

  //here for later implementation

  std::stringstream levelStr;

  levelStr << "Level: " << playerLevel;
  levelHUD = TTF_RenderText_Solid(font18, levelStr.str().c_str(), font18Color);

  apply_surface(5, 18, levelHUD, screen);

  SDL_FreeSurface(levelHUD);
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
	  delete *it;
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

void showText(const char* text, TTF_Font *font, SDL_Color color, int x, int y)
{
  SDL_Surface *ttfRender = TTF_RenderText_Solid(font, text, color);

  apply_surface(x, y, ttfRender, screen);

  SDL_FreeSurface(ttfRender);
}

const char* intToString(int i)
{
  std::stringstream ss;
  ss << i;
  return ss.str().c_str();
}

//removes all enemies
void resetEnemies()
{
  for(std::list<Grunt*>::iterator it = grunts.begin(); it != grunts.end();)
    {
      delete * it;
      grunts.erase(it++);
    }

  for(std::list<Boomer*>::iterator it = boomers.begin(); it != boomers.end();)
    {
      delete * it;
      boomers.erase(it++);
    }

  for(std::list<Stealth*>::iterator it = stealths.begin();
      it != stealths.end();)
    {
      delete *it;
      stealths.erase(it++);
    }

  for(std::list<Carrier*>::iterator it = carriers.begin();
      it != carriers.end();)
    {
      delete *it;
      carriers.erase(it++);
    }
}

void playSound(Mix_Chunk *sound)
{
  if(mute == false)
    Mix_PlayChannel(-1, sound, 0);
}
