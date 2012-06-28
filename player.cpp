//player.cpp

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include <math.h>
#include <iostream>
#include <list>

#include "constants.h"
#include "classes.h"
#include "functions.h"
#include "globals.h"



Player::Player()
{
  isPlayer = true;

  radius = 20;

  //offset
  x = 1000;
  y = 1000;

  //velocity
  xVel = 0;
  yVel = 0;

  x1 = 0;
  y1 = 1;

  //default weapon (lclick)
  weapon = 1;


  //default weapon attributes

  //molten slug
  MS_speed = 20;
  MS_damage = 10;
  MS_radius = 5;
  MS_range = 400;
  MS_rate = 10;

  lmouse = false;
  rmouse = false;

  up = false;
  down = false;
  left = false;
  right = false;

  maxHull = 100;
  hull = 100;

  maxArmor = 100;
  armor = 100;

  maxShield = 100;
  shield = 100;

  maxEnergy = 100;
  energy = 100;
}

void Player::handle_input()
{
  //If a key was pressed
  if( event.type == SDL_KEYDOWN )
    {
      //Adjust the velocity
      switch( event.key.keysym.sym )
        {
	case SDLK_UP: up = true; break;
	case SDLK_DOWN: down = true; break;
	case SDLK_LEFT: left = true; break;
	case SDLK_RIGHT: right = true; break;    
        }
    }
  //If a key was released
  else if( event.type == SDL_KEYUP )
    {
      //Adjust the velocity
      switch( event.key.keysym.sym )
        {
	case SDLK_UP: up = false; break;
	case SDLK_DOWN: down = false; break;
	case SDLK_LEFT: left = false; break;
	case SDLK_RIGHT: right = false; break;    
        }        
    }

  //mouse motion
  if(event.type == SDL_MOUSEMOTION)
    {
      mouseX = event.motion.x;
      mouseY = event.motion.y;
    }

  if(event.type == SDL_MOUSEBUTTONDOWN)
    {
      //left mouse button
      if(event.button.button == SDL_BUTTON_LEFT)
	lmouse = true;
      if(event.button.button == SDL_BUTTON_RIGHT)
	rmouse = true;
    }

  if(event.type == SDL_MOUSEBUTTONUP)
    {
      //left mouse button
      if(event.button.button == SDL_BUTTON_LEFT)
	lmouse = false;

      if(event.button.button == SDL_BUTTON_RIGHT)
	rmouse = false;
    }
}

void Player::faceMouse()
{
  //mouse offsets
  int mX = mouseX;
  int mY = mouseY;
  int sX = SCREEN_WIDTH / 2;
  int sY = SCREEN_HEIGHT / 2;
      
  if(x < SCREEN_WIDTH / 2)
    sX = x;
  else if(x > LEVEL_WIDTH - SCREEN_WIDTH / 2)
    sX = SCREEN_WIDTH - (LEVEL_WIDTH - x);
  
  if(y < SCREEN_HEIGHT / 2)
    sY = y;
  else if(y > LEVEL_HEIGHT - SCREEN_HEIGHT / 2)
    sY = SCREEN_HEIGHT - (LEVEL_HEIGHT - y);
  
  double hypo = distForm(sX, sY, mX, mY);
  
  //update direction
  x1 = (mX - sX) / hypo;
  y1 = (mY - sY) / hypo;
  
  double angle;
  
  if(mY - sY == 0)
    {
      if(mX > sX)
	angle = -90;
      else
	angle = 90;
    }
  
  else
    {
      if(sX > mX && mY < sY)
	{
	  angle = atan(((double)(sX - mX)) / (sY - mY)) * 180.0 / PI;
	}
      else if(sX > mX && mY > sY)
	{
	  angle = 180 -atan(((double)(sX - mX)) / (mY - sY)) * 180.0 / PI;
	}
      else if(sX < mX && mY < sY)
	{
	  angle = -atan(((double)(mX - sX)) / (sY - mY)) * 180.0 / PI;
	}
      else //(sX < mX && mY > sY)
	{
	  angle= -180 + atan(((double)(mX - sX)) / (mY - sY)) * 180.0 / PI;
	}
    }
  
  //rotate image
  ship = rotate(player, angle, 1, 0);
}

void Player::accelerate()
{
  if(up)
    yVel -= 1;
  if(down)
    yVel += 1;
  if(left)
    xVel -= 1;
  if(right)
    xVel += 1;
}

void Player::doLeftClick()
{
  if(lmouse == true)
    {
      if(weapon == 1 && frame % MS_rate == 0)
	{
	  shootMoltenSlug();
	}
    }
}

void Player::set_camera()
{
  //Center the camera over the camera
  camera.x = ( x + radius) - SCREEN_WIDTH / 2;
  camera.y = ( y + radius) - SCREEN_HEIGHT / 2;
    
  int cameraXold = camera.x;
  int cameraYold = camera.y;

  //Keep the camera in bounds.
  if( camera.x < 0 )
    {
      camera.x = 0;    
    }
  if( camera.y < 0 )
    {
      camera.y = 0;    
    }
  if( camera.x > LEVEL_WIDTH - camera.w )
    {
      camera.x = LEVEL_WIDTH - camera.w;    
    }
  if( camera.y > LEVEL_HEIGHT - camera.h )
    {
      camera.y = LEVEL_HEIGHT - camera.h;    
    }
}

int Player::getEnergy()
{
  return energy;
}

void Player::updateStatusBars()
{

  playerShield.w = int(200 * (double(shield) / maxShield));
  playerArmor.w = int(200 * (double(armor) / maxArmor));
  playerHull.w = int(200 * (double(hull) / maxHull));
  playerEnergy.w = int(200 * (double(energy) / maxEnergy));
}

void Player::doUnit()
{
  updateStatusBars();
  accelerate();
  move();
  faceMouse();
  set_camera();

  //do actions
  doLeftClick();

  //move projectiles
  moveProjectiles(slugs);
  show();
}
