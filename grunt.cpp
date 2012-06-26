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
  //std::cout << grunt == NULL;
  //ship = player;

  target = player0;

  x = startx;
  y = starty;

  xVel = 0;
  yVel = 0;

  //not used int grunt
  x1 = 0;
  y1 = 1;

  maxShield = 20;
  maxArmor = 20;
  maxHull = 20;

  shield = 20;
  armor = 20;
  hull = 20;
}

//accelerate towards player, but not crashing into
void Grunt::accelerate()
{

  /* */
  ship = grunt;

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

void Grunt::shootBullets()
{
  if(frame % 10 == 0)
    {
      /* put into projectile class? */

      //predict player position
      int playerX = (*target).getX() + 5 * (*target).getXvel();
      int playerY = (*target).getY() + 5 * (*target).getYvel();
      
      int dist = distForm(x, y, playerX, playerY);

      x1 = double(playerX - x) / dist;
      y1 = double(playerY - y) / dist;
      
      //should fix bullets to be vectors
      //molten slug speed
      int slugSpeed = 20;
      int slugDamage = 10;
      int slugRad = 5;
      int slugRange = 800;
      
      Projectile* shot = new Projectile(moltenSlug, x, y, x1, y1,
                                        slugDamage, slugSpeed, slugRad,
                                        slugRange);
      
      slugs.push_back(shot);
    }
}

void Grunt::moveBullets()
{
  /* put this into projectile class? */
  //metal slugs
  for(std::list<Projectile*>::iterator it = slugs.begin(); it != slugs.end();)
    {
      //move bullet, remove if max range/out of bounds
      (**it).move();
      (**it).show();

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
