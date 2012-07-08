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
  ability = 1;

  //default weapon attributes

  //molten slug
  MS_speed = 30;
  MS_damage = 10;
  MS_radius = 5;
  MS_range = 600;
  MS_rate = 20;

  //mini gun
  MG_speed = 20;
  MG_damage = 3;
  MG_radius = 4;
  MG_range = 400;
  MG_rate = 4;

  //shotgun
  SG_speed = 20;
  SG_damage = 8;
  SG_radius = 5;
  SG_range = 400;
  SG_rate = 30;

  //homing missiles
  homing_speed = 10;
  homing_damage = 10;
  homing_radius = 5;
  homing_range = 800;
  homing_rate = 30;

  lmouse = false;
  rmouse = false;

  lStart = 0;
  rStart = 0;

  up = false;
  down = false;
  left = false;
  right = false;

  maxHull = 100;
  hull = 100;

  maxArmor = 100;
  armor = 100;

  shieldRegen = 1;
  maxShield = 100;
  shield = 100;

  energyRegen = 1;
  maxEnergy = 100;
  energy = 100;

  //abilities
  shieldRepFact = 1;
}

void Player::regenEnergy()
{
  if(energy < maxEnergy && frame % 10 == 0)
    energy += energyRegen * maxEnergy / 100;
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

	case SDLK_1: weapon = 1; break;
	case SDLK_2: weapon = 2; break;
	case SDLK_3: weapon = 3; break;
	case SDLK_4: weapon = 4; break;
	case SDLK_5: weapon = 5; break;
	
	default: void(); break;
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
	default: void(); break;
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
	{
	  lmouse = true;
	  //lStart = frame;
	}
      if(event.button.button == SDL_BUTTON_RIGHT)
	{
	  rmouse = true;
	  //rStart = frame;
	}
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
  
  double angle = (unitToAngle(x1, y1) - PI / 2) * 180.0 / PI;
  
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
  if(lStart > 0)
    lStart--;

  if(lmouse == true && lStart == 0)
    {

      //maybe allow multiple weapons?
      if(weapon == 1)
	{
	  lStart = MS_rate;
	  shootProjectile(moltenSlug, MS_speed, MS_range, MS_damage,
			  MS_radius);
	}
      else if(weapon == 2)
	{
	  lStart = MG_rate;
	  shootProjectile(miniGun, MG_speed, MG_range, MG_damage, MG_radius);
	}
      else if(weapon == 3)
	{
	  lStart = SG_rate;
	  shootShotgun();
	}
      else if(weapon == 4)
	{
	  lStart = homing_rate;
	  shootHoming();
	}
    }
}

void Player::doRightClick()
{
  if(rStart > 0)
    rStart--;
  
  if(rmouse == true && rStart == 0)
    {
      if(ability == 1 && energy > 0)
	{
	  apply_surface(x - camera.x - 25, y - camera.y - 25,
			shield_rep, screen,
			&shield_rep_frames[(frame % 16) / 4]);

	  shield += shieldRepFact;
	  if(shield > maxShield)
	    shield = maxShield;
	  energy -= 1;
	}
    }
}

void Player::set_camera()
{
  //Center the camera over the camera
  camera.x = ( x + radius) - SCREEN_WIDTH / 2;
  camera.y = ( y + radius) - SCREEN_HEIGHT / 2;
    
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
  regenShield();
  regenEnergy();
  updateStatusBars();
  accelerate();
  move();
  faceMouse();
  set_camera();

  //do actions
  doLeftClick();

  //move projectiles
  slugs = moveProjectiles(slugs);
  show();
  doRightClick();
}
