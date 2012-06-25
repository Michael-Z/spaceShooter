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
  //offset
  x = 1000;
  y = 1000;

  //velocity
  xVel = 0;
  yVel = 0;

  lmouse = false;
  rmouse = false;

  up = false;
  down = false;
  left = false;
  right = false;

  hull = 100;
  armor = 100;
  shield = 100;
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
      if(event.button.button = SDL_BUTTON_LEFT)
	lmouse = true;
      if(event.button.button = SDL_BUTTON_RIGHT)
	rmouse = true;
    }
  if(event.type == SDL_MOUSEBUTTONUP)
    {
      //left mouse button
      if(event.button.button = SDL_BUTTON_LEFT)
	lmouse = false;
      if(event.button.button = SDL_BUTTON_RIGHT)
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
  
  
  double hypo = sqrt(((double)(pow(mX - sX, 2) + pow(mY - sY, 2))));
  
  //update direction
  x1 = (mX - sX) / hypo;
  y1 = (mY - sY) / hypo;
  
  //std::cout << x1 << " " << y1 << std::endl;
  
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
  playerRotated = rotate(player, angle, 1, 0);
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

void Player::moveBullets()
{
  //metal slugs
  for(std::list<Projectile*>::iterator it = slugs.begin(); it != slugs.end();)
    {
      //move bullet, remove if max range/out of bounds
      (**it).move();

      if((**it).getDist() > (**it).getRange()  || (**it).isOutBounds())
	{
	  //delete(*it);
	  slugs.erase(it++); //remove from list take next
	}

      //check collision
      else if(false)
	{
	  void();
	  //collision check
	  //iterate through enemies and check if it collided
	  //*it.collide();
	}
      else
	{
	  ++it; //take next object
	}
    }
}

void Player::shootBullets()
{
  if(lmouse == true && frame % 10 == 0)
    {
      //should fix bullets to be vectors
      //molten slug speed
      int slugSpeed = 20;
      int slugDamage = 10;
      int slugRad = 5;
      int slugRange = 300;
      
      Projectile* shot = new Projectile(moltenSlug, x, y, x1, y1,
					slugDamage, slugSpeed, slugRad,
					slugRange);
      
      slugs.push_back(shot);
    }
}

void Player::showBullets()
{
  //metal slugs
  for(std::list<Projectile*>::iterator it = slugs.begin(); it != slugs.end();
      it++)
    {
      (**it).show();
    }
}

void Player::set_camera()
{
  //Center the camera over the camera
  camera.x = ( x + SHIP_WIDTH / 2 ) - SCREEN_WIDTH / 2;
  camera.y = ( y + SHIP_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;
    
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

void Player::show()
{    
  //Show the player
  apply_surface( x - camera.x - SHIP_WIDTH / 2
		 , y - camera.y - SHIP_WIDTH / 2
		 , playerRotated, screen );
}

