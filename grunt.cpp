#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include <iostream>
#include <list>
#include <math.h>

#include "constants.h"
#include "classes.h"
#include "functions.h"
#include "globals.h"

Grunt::Grunt(int startx, int starty, Ship *player0)
{
  isPlayer = false;
  target = player0;
  score = 20;

  radius = 30;
  maxSpeed = 20;

  x = startx;
  y = starty;

  xVel = 0;
  yVel = 0;

  x1 = 0;
  y1 = 1;

  maxShield = 10;
  maxArmor = 10;
  maxHull = 10;

  shield = 10;
  armor = 10;
  hull = 10;

  //Molten Slug info
  MS_speed = 30;
  MS_damage = 10;
  MS_radius = 5;
  MS_range = 600;
  MS_rate = 20;
}

/* useless */
Grunt::~Grunt()
{
  void();
}

//accelerate towards player, but not crashing into
void Grunt::accelerate()
{
  int playerX = (*target).getX();
  int playerY = (*target).getY();

  int dist = distForm(x, y, playerX, playerY);
  
  //too far move closer
  if(dist > 300)
    {
      if(playerX > x && xVel < maxSpeed) xVel += 1;
      else if(playerX - x && xVel > -maxSpeed) xVel -= 1;
      
      
      if(playerY > y && yVel < maxSpeed) yVel += 1;
      else if(playerY - y && yVel > -maxSpeed) yVel -= 1;
    }
  else if(dist < 150) // too close
    {
      if(playerX > x && xVel > -maxSpeed) xVel -= 1;
      else if(playerX < x && xVel < maxSpeed) xVel += 1;

      if(playerY > y && yVel > -maxSpeed) yVel -= 1;
      else if(playerY < y && yVel < maxSpeed) yVel += 1;
    }

  //try to avoid crashing into walls
  if(LEVEL_WIDTH - x < 150 && xVel > -maxSpeed) xVel -= 2;
  else if(x < 150 && xVel < maxSpeed) xVel += 2;

  if(LEVEL_HEIGHT - y < 150 && yVel > -maxSpeed) yVel -= 2;
  else if(y < 150 && yVel < maxSpeed) yVel += 2;

}

void Grunt::doUnit(std::list<Grunt*>::iterator it)
{
  //set picture
  if(ship != grunt)
    ship = grunt;

  accelerate();


  //int dist;
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
      int playerX = (*target).getX() + 5 * (*target).getXvel() - 5 * xVel;
      int playerY = (*target).getY() + 5 * (*target).getYvel() - 5 * yVel;
      faceDirection(playerX, playerY);
      shootProjectile(moltenSlug, MS_speed, MS_range, MS_damage, MS_radius);
    }

  slugs = moveProjectiles(slugs);
  show();
}
