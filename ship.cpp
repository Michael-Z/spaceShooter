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

void Ship::unMove()
{
  x -= xVel;
  y -= yVel;
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
	      die();
	    }
	}
	  
    }
}

void Ship::shootMoltenSlug()
{
  //should fix bullets to be vectors

  int sXvel = xVel + int(MS_speed * x1);
  int sYvel = yVel + int(MS_speed * y1);
  
  //prevent projectiles from going too slow
  if(distForm(0, 0, sXvel, sYvel) < MS_speed / 2)
    {
      sXvel = int((MS_speed) / 2 * x1);
      sYvel = int((MS_speed) / 2 * y1);
    }
  int flight_time = MS_range / MS_speed; //flight time in frames
  int range = flight_time * int(distForm(0, 0, sXvel, sYvel));

  Projectile *shot = new Projectile(moltenSlug, x, y, sXvel, sYvel,
				    MS_damage, MS_radius, range);
  slugs.push_back(shot);
}

std::list<Projectile*> Ship::moveProjectiles(std::list<Projectile*> bullets)
{
  for(std::list<Projectile*>::iterator it = bullets.begin();
      it != bullets.end();)
    {

      //move bullet, remove if max range/out of bounds, show bullet
      (**it).move();

      if(isPlayer == false)
	{
	  if(distForm((*target).getX(), (*target).getY(), (**it).getX(),
		      (**it).getY()) < (*target).getRad() + (**it).getRad())
	    {
	      (*target).takeDamage((**it).getDamage());
	      delete *it;
	      bullets.erase(it++);
	      goto end;
	    }
	  else
	    goto next;
	}
      else //its the player, check enemy lists
	{
	  for(std::list<Grunt*>::iterator g = grunts.begin();
	      g != grunts.end(); g++)
	    {
	      if(distForm((**g).getX(), (**g).getY(), (**it).getX(),
			 (**it).getY()) < (**g).getRad() + (**it).getRad())
		{
		  (**g).takeDamage((**it).getDamage());
		  delete *it;
		  bullets.erase(it++);
		  goto end;
		}
	    }
	  goto next;
	}
    next:
      if((**it).getDist() > (**it).getRange()  || (**it).isOutBounds())
        {
          //delete(*it);
	  delete(*it);
          bullets.erase(it++); //remove from list take next

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
	  (**it).show();
	  ++it;
	}
    end:
      void();
    }
  return bullets;
}

void Ship::die()
{
  explosions.push_back(new Explosion(x, y));
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

int Ship::getRad()
{
  return radius;
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
