//boomer.cpp

#include "classes.h"
#include "globals.h"
#include "functions.h"

Boomer::Boomer(int startx, int starty, Player* player)
{
  isPlayer = false;
  target = player;

  radius = 10;
  maxSpeed = 20;

  x = startx;
  y = starty;
  
  xVel = 0;
  yVel = 0;

  damage = 20;

  maxShield = 1;
  maxArmor = 1;
  maxHull = 1;

  shieldRegen = 0;
  shield = 1;
  armor = 1;
  hull = 1;
}

void Boomer::accelerate()
{
  int tX = target->getX();
  int tY = target->getY();
  int tXvel = target->getXvel();
  int tYvel = target->getYvel();

  int dist = distForm(x, y, tX, tY);

  //lead factor for acceleration;
  int lF = int(distForm(0, 0, tXvel, tYvel)) / 4;

  if(dist < 5 * radius)
    {
      die();
      return;
    }

  if((tX + lF * tXvel > x) && xVel < maxSpeed)
    {
      xVel += 1;
    }
  else if((tX + lF * tXvel < x) && (-xVel < maxSpeed))
    {
      xVel -= 1;
    }
	  
  if((tY + lF * tYvel > y) && yVel < maxSpeed)
    {
      yVel += 1;
    }
  else if((tY + lF * tYvel < y) && (-yVel < maxSpeed))
    {
      yVel -=1;
    }
}

void Boomer::doUnit()
{
  if(ship != boomer)
    ship = boomer;

  accelerate();
  move();
  show();
}

void Boomer::die()
{
  shield = 0;
  armor = 0;
  hull = 0;
  
  explosions.push_back(new Explosion(x, y));
  if(distForm(x, y, (target)->getX(), (target)->getY()) < 5 * radius)
    (target)->takeDamage(damage);
}
