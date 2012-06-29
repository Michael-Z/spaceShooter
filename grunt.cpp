#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include <iostream>
#include <list>
#include <math.h>

#include "constants.h"
#include "classes.h"
#include "functions.h"
#include "globals.h"

Grunt::Grunt(int startx, int starty, Player *player0)
{
  isPlayer = false;
  target = player0;

  radius = 30;

  x = startx;
  y = starty;

  xVel = 0;
  yVel = 0;

  x1 = 0;
  y1 = 1;

  maxShield = 20;
  maxArmor = 20;
  maxHull = 20;

  shield = 20;
  armor = 20;
  hull = 20;

  //Molten Slug info
  MS_speed = 20;
  MS_damage = 10;
  MS_radius = 5;
  MS_range = 400;
  MS_rate = 10;
}

Grunt::~Grunt()
{
  void();
}

//accelerate towards player, but not crashing into
void Grunt::accelerate()
{
  int maxSpeed = 10; //frames per pixel
  
  int playerX = (*target).getX();
  int playerY = (*target).getY();

  int dist = distForm(x, y, playerX, playerY);
  
  //too far move closer
  if(dist > 300)
    {
      if(playerX > x) xVel += 1;
      else xVel -= 1;
      
      
      if(playerY > y) yVel += 1;
      else yVel -= 1;
    }
  if(dist < 150) // too close
    {
      if(playerX > x) xVel -= 1;
      else xVel += 1;

      if(playerY > y) yVel -= 1;
      else yVel += 1;
    }
  int oldXvel = xVel;
  int oldYvel = yVel;

  if(abs(xVel) > maxSpeed)
    {
      if(xVel > 0)
	xVel = maxSpeed;
      else
	xVel = -maxSpeed;
    }

  if(abs(yVel) > maxSpeed)
    {
      if(yVel > 0)
	yVel = maxSpeed;
      else
	yVel = -maxSpeed;
    }
}

void Grunt::doUnit(std::list<Grunt*> grunts, std::list<Grunt*>::iterator it)
{
  //set picture
  if(ship != grunt)
    ship = grunt;

  accelerate();


  int dist;
  //int ixVel;
  //int iyVel;

  move();

  //need to improve this to not repeat
  //it++;
  for(std::list<Grunt*>::iterator i = grunts.begin()/*it*/; i != grunts.end(); i++)
    {
      if(i != it)
	{
	  int dist = distForm(x, y, (**i).getX(), (**i).getY());
	  if(dist < radius * 2 && dist > 0)
	    {
	      unMove();
	      //ixVel = (**i).getXvel();
	      //iyVel = (**i).getYvel();

	      //bounce off each other
	      //if(!((xVel > 0 && ixVel > 0) || (xVel < 0 && ixVel < 0)))
		xVel = -xVel / 2;
		//if(!((yVel > 0 && iyVel > 0) || (yVel < 0 && iyVel < 0)))
		yVel = -yVel / 2;
	    }
	}
    }

  //face target and shoot
  if(frame % MS_rate == 0)
    {
      //predict player position
      int playerX = (*target).getX() + 5 * (*target).getXvel();
      int playerY = (*target).getY() + 5 * (*target).getYvel();
      faceDirection(playerX, playerY);
      shootMoltenSlug();
    }

  slugs = moveProjectiles(slugs);
  show();
}
