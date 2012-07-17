//carrier.cpp

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include <list>

#include "constants.h"
#include "classes.h"
#include "functions.h"
#include "globals.h"

Carrier::Carrier(int startx, int starty, Ship *player0)
{
  isPlayer = false;
  target = player0;
  score = 200;

  radius = 50;
  maxSpeed = 10;

  x = startx;
  y = starty;

  xVel = 0;
  yVel = 0;

  x1 = 0;
  y1 = 1;

  evasion = 0;
  hitRadius = radius;
  damRed = 0;

  maxShield = 50;
  maxArmor = 50;
  maxHull = 100;

  shieldRegen = 2;
  shieldCap = false;
  shield = 50;
  armor = 50;
  hull = 100;

  //molten slug info
  MS_speed = 50;
  MS_damage = 20;
  MS_radius = 10;
  MS_range = 1000;
  MS_rate = 20;
}

//keep distance 800, but don't crash into walls
void Carrier::accelerate()
{
  int playerX = target->getX();
  int playerY = target->getY();

  int dist = distForm(x, y, playerX, playerY);

  //get closer
  if(dist > 600)
    {
      if(playerX > x && xVel < maxSpeed)
	xVel += 1;
      else if(playerX < x && xVel > -maxSpeed)
	xVel -= 1;

      if(playerY > y && yVel < maxSpeed)
	yVel += 1;
      else if(playerY < y && yVel > -maxSpeed)
	yVel -= 1;
    }
  else if(dist  < 400)
    {
      if(playerX > x && xVel > -maxSpeed)
	xVel -= 1;
      else if(playerX < x && xVel < maxSpeed)
	xVel += 1;

      if(playerY > y && yVel > -maxSpeed)
	yVel -= 1;
      else if(playerY < y && yVel < maxSpeed)
	yVel += 1;
    }

  //tryto avoid crashing into walls                                            
  if(LEVEL_WIDTH - x < 200 && xVel > -maxSpeed) xVel -=2;
  else if(x < 200 && xVel < maxSpeed) xVel += 2;

  if(LEVEL_HEIGHT - y < 200 && yVel > -maxSpeed) yVel -= 2;
  else if(y < 200 && yVel < maxSpeed) yVel += 2;

}

void Carrier::doUnit(std::list<Carrier*>::iterator it)
{
  if(ship != carrier)
    ship = carrier;

  accelerate();
  regenShield();

  move();

  for(std::list<Carrier*>::iterator i = it; i != carriers.end(); i++)
    {
      if(i != it)
	{
	  int dist = distForm(x, y, (**i).getX(), (**i).getY());
	  if(dist < radius * 2)
	    unMove();
	}
    }

  if(frame % MS_rate == 0)
    {
      int playerX = target->getX() + 5 * target->getXvel() - 5 * xVel;
      int playerY = target->getY() + 5 * target->getYvel() - 5 * yVel;
      faceDirection(playerX, playerY);
      shootProjectile(moltenSlug, MS_speed, MS_range, MS_damage, MS_radius);
	
    }

  //launch boomers
  if(frame % 80 == 0)
    {
      boomers.push_back(new Boomer(x - radius, y - radius, target, -10, -10));
      boomers.push_back(new Boomer(x - radius, y + radius, target, -10, +10));
      boomers.push_back(new Boomer(x + radius, y - radius, target, +10, -10));
      boomers.push_back(new Boomer(x + radius, y + radius, target, +10, +10));

    }

  slugs = moveProjectiles(slugs);

  show();
}

void Carrier::die()
{
  explosions.push_back(new Explosion(x - radius, y - radius));
  explosions.push_back(new Explosion(x - radius, y + radius));
  explosions.push_back(new Explosion(x + radius, y - radius));
  explosions.push_back(new Explosion(x + radius, y + radius));
}
