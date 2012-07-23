//boomer.cpp

#include "classes.h"
#include "globals.h"
#include "constants.h"
#include "functions.h"

//initialize boomer variables
int Boomer::unit_score = 10;
int Boomer::unit_shield = 1;
int Boomer::unit_armor = 1;
int Boomer::unit_hull = 1;
int Boomer::unit_damage = 20;

Boomer::Boomer(int startx, int starty, Ship* player, int startxVel,
	       int startyVel)
{
  isPlayer = false;
  target = player;
  score = unit_score;

  radius = 10;
  maxSpeed = 20;

  x = startx;
  y = starty;
  
  xVel = startxVel;
  yVel = startyVel;

  damage = unit_damage;

  evasion = 0;
  hitRadius = radius;
  damRed = 0;

  maxShield = unit_shield;
  maxArmor = unit_armor;
  maxHull = unit_hull;

  shield = maxShield;
  armor = maxArmor;
  hull = maxHull;
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

  //tryto avoid crashing into walls                                            
  if(LEVEL_WIDTH - x < 100 && xVel > -maxSpeed) xVel -=2;
  else if(x < 100 && xVel < maxSpeed) xVel += 2;

  if(LEVEL_HEIGHT - y <100 && yVel > -maxSpeed) yVel -= 2;
  else if(y < 100 && yVel < maxSpeed) yVel += 2;

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
