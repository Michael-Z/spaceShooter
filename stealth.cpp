#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include <list>

#include "constants.h"
#include "classes.h"
#include "functions.h"
#include "globals.h"

Stealth::Stealth(int startx, int starty, Ship *player0)
{
  isPlayer = false;
  target = player0;
  score = 50;

  radius = 15;
  maxSpeed = 15;

  x = startx;
  y = starty;

  xVel = 0;
  yVel = 0;

  x1 = 0;
  y1 = 1;

  maxShield = 50;
  maxArmor = 10;
  maxHull = 10;

  shieldRegen = 2;
  shield = 50;
  armor = 10;
  hull = 10;

  //miniGun Info
  MG_speed = 30;
  MG_damage = 3;
  MG_radius = 4;
  MG_range = 400;
  MG_rate = 4;
  MG_double = false;
}

//orbit target
void Stealth::accelerate()
{
  
  int playerX = target->getX();
  int playerY = target->getY();

  if(playerX > x && xVel < maxSpeed)
    {
      if(playerX - x > 200)
	xVel += 1;
    }
  else if(playerX < x && xVel > -maxSpeed)
    {
      if(x - playerX > 200)
	xVel -= 1;
    }
  
  if(playerY > y && yVel < maxSpeed)
    {
      if(playerY - y > 200)
	yVel += 1;
    }
  else if(playerY < y && yVel > -maxSpeed)
    {
      if(y - playerY > 200)
	yVel -= 1;
    }

  //tryto avoid crashing into walls                                            
  if(LEVEL_WIDTH - x < 150 && xVel > -maxSpeed) xVel -=2;
  else if(x < 150 && xVel < maxSpeed) xVel += 2;

  if(LEVEL_HEIGHT - y <150 && yVel > -maxSpeed) yVel -= 2;
  else if(y < 150 && yVel < maxSpeed) yVel += 2;

}

void Stealth::doUnit(std::list<Stealth*>::iterator it)
{
  //set picture
  if(ship != stealth)
    ship = stealth;

  accelerate();
  regenShield();

  move();

  for(std::list<Stealth*>::iterator i = it; i != stealths.end(); i++)
    {
      if(i != it)
	{
	  int dist = distForm(x, y, (**i).getX(), (**i).getY());
	  if(dist < radius * 2)
	    unMove();
	}
    }

  //face target and shoot
  if(frame % MG_rate == 0)
    {
      int playerX = target->getX() + 5 * target->getXvel() - 5 * xVel;
      int playerY = target->getY() + 5 * target->getYvel() - 5 * yVel;
      faceDirection(playerX, playerY);
      shootProjectile(miniGun, MG_speed, MG_range, MG_damage, MG_radius);
    }

  slugs = moveProjectiles(slugs);

  show();
}
