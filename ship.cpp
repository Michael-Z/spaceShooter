//ship.cpp

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_rotozoom.h"
#include <string>
#include <list>
#include <iostream>

#include "constants.h"
#include "classes.h"
#include "functions.h"
#include "globals.h"

void Ship::move()
{
  //Move the ship left or right
  x += xVel;
    
  //If the ship went too far to the left or right
  if( ( x < radius) || ( x + radius > LEVEL_WIDTH ) )
    {
      //move back
      x -= xVel;
      takeDamage(abs(xVel) * 4);
      xVel = -xVel / 2; //ricochet
    }
    
  //Move the ship up or down
  y += yVel;
    
  //If the ship went too far up or down
  if( ( y < radius) || ( y + radius > LEVEL_HEIGHT ) )
    {
      //move back
      y -= yVel;
      takeDamage(abs(yVel) * 4);
      yVel = -yVel / 2;
    }
}

void Ship::faceDirection(int tX, int tY)
{
  int dist = distForm(x, y, tX, tY);
    
  x1 = double(tX - x) / dist;
  y1 = double(tY - y) / dist;
}

void Ship::show()
{
  apply_surface(x - camera.x - radius,
                y - camera.y - radius,
                ship, screen );
}

void Ship::takeDamage(int damage)
{
  if(shield - damage > 0)
    shield -= damage;
  else
    {
      damage -= shield;
      shield = 0;

      if(armor - damage > 0)
	armor -= damage;
      else
	{
	  damage -= armor;
	  armor = 0;
	  
	  if(hull - damage > 0)
	      hull -= damage;
	  else
	    {
	      hull = 0;
	      /*gameOver(); */
	    }
	}
	  
    }
}

void Ship::shootMoltenSlug()
{
  //should fix bullets to be vectors
  Projectile* shot = new Projectile(moltenSlug, x, y, x1, y1,
				    MS_damage, MS_speed, MS_radius,
				    MS_range);
  slugs.push_back(shot);
}

void Ship::moveProjectiles(std::list<Projectile*> bullets)
{
  for(std::list<Projectile*>::iterator it = bullets.begin();
      it != bullets.end();)
    {
      //move bullet, remove if max range/out of bounds, show bullet
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
	(**it).show();
	++it; //take next moltenSlug
    }
}

int Ship::getShield()
{
  return shield;
}

int Ship::getArmor()
{
  return armor;
}

int Ship::getHull()
{
  return hull;
}

int Ship::getX()
{
  return x;
}

int Ship::getY()
{
  return y;
}

int Ship::getXvel()
{
  return xVel;
}

int Ship::getYvel()
{
  return yVel;
}

double Ship::getxDir()
{
  return x1;
}

double Ship::getyDir()
{
  return y1;
}
