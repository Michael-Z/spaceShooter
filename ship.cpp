//ship.cpp

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_rotozoom.h"
#include "SDL/SDL_mixer.h"

#include <string>
#include <list>
#include <iostream>

#include "constants.h"
#include "classes.h"
#include "functions.h"
#include "globals.h"

Ship::~Ship()
{
  //delete all the projectiles
  for(std::list<Projectile*>::iterator it = slugs.begin(); it != slugs.end();)
    {
      delete *it;
      slugs.erase(it++);
    }
}

void Ship::move()
{
  //Move the ship left or right
  x += xVel / 2;

  //If the ship went too far to the left or right
  if( ( x < radius) || ( x + radius > LEVEL_WIDTH ) )
    {
      //move back
      x -= xVel;
      takeDamage(abs(xVel) * 2);
      xVel = -xVel / 2; //ricochet
    }
    
  //Move the ship up or down
  y += yVel / 2;
    
  //If the ship went too far up or down
  if( ( y < radius) || ( y + radius > LEVEL_HEIGHT ) )
    {
      //move back
      y -= yVel;
      takeDamage(abs(yVel) * 4);
      yVel = -yVel / 2;
    }
}

void Ship::regenShield()
{
  if(shield < maxShield && frame % 10 == 0)
    shield += shieldRegen * maxShield / 100;
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
	      playerScore += score;
	      die();
	    }
	}
	  
    }
}

void Ship::shootProjectile(SDL_Surface *image, int speed, int range,
			   int damage, int radius, bool isHoming)
{
  int sXvel = xVel + int(speed * x1);
  int sYvel = yVel + int(speed * y1);

  //prevent projectiles from going too slow
  if(distForm(0, 0, sXvel, sYvel) < speed / 2)
    {
      sXvel = int((speed) / 2 * x1);
      sYvel = int((speed) / 2 * y1);
    }
  int flight_time = range / speed; //flight time in frames
  int rangeMod = flight_time * int(distForm(0, 0, sXvel, sYvel));

  Projectile *shot = new Projectile(image, x, y, sXvel, sYvel,
                                    damage, radius, rangeMod, isHoming);
  slugs.push_back(shot);

}

void Ship::shootShotgun()
{
  double x1old = x1;
  double y1old = y1;

  double angle = unitToAngle(x1, y1);

  shootProjectile(shotgun, SG_speed, SG_range, SG_damage, SG_radius);

  x1 = angleToUnitX(angle + PI / 8);
  y1 = angleToUnitY(angle + PI / 8);

  shootProjectile(shotgun, SG_speed, SG_range, SG_damage, SG_radius);

  x1 = angleToUnitX(angle - PI / 8);
  y1 = angleToUnitY(angle - PI / 8);

  shootProjectile(shotgun, SG_speed, SG_range, SG_damage, SG_radius);


  x1 = angleToUnitX(angle + PI / 16);
  y1 = angleToUnitY(angle + PI / 16);

  shootProjectile(shotgun, SG_speed, SG_range, SG_damage, SG_radius);

  x1 = angleToUnitX(angle - PI / 16);
  y1 = angleToUnitY(angle - PI / 16);

  shootProjectile(shotgun, SG_speed, SG_range, SG_damage, SG_radius);
  
  x1 = x1old;
  y1 = y1old;
}

void Ship::shootHoming()
{
  double x1old = x1;
  double y1old = y1;

  double angle = unitToAngle(x1, y1);
  x1 = angleToUnitX(angle + PI / 4);
  y1 = angleToUnitY(angle + PI / 4);

  shootProjectile(homing, homing_speed, homing_range, homing_damage,
		  homing_radius, true);

  x1 = angleToUnitX(angle - PI / 4);
  y1 = angleToUnitY(angle - PI / 4);

  shootProjectile(homing, homing_speed, homing_range, homing_damage,
		  homing_radius, true);

  x1 = x1old;
  y1 = y1old;
}

void Ship::shootMGdouble()
{
  int oldX = x;
  int oldY = y;

  double angle = unitToAngle(x1, y1);

  double x1temp = angleToUnitX(angle - PI / 2);
  double y1temp = angleToUnitY(angle - PI / 2);

  y = oldY + int(radius / 2 * y1temp);
  x = oldX + int(radius / 2 * x1temp);
  
  shootProjectile(miniGun, MG_speed, MG_range, MG_damage, MG_radius);
  
  x1temp = angleToUnitX(angle + PI / 2);
  y1temp = angleToUnitY(angle + PI / 2);

  y = oldY + int(radius / 2 * y1temp);
  x = oldX + int(radius / 2 * x1temp);

  shootProjectile(miniGun, MG_speed, MG_range, MG_damage, MG_radius);

  x = oldX;
  y = oldY;
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
	  if((**it).isHoming())
	    (**it).doHoming((*target).getX(), (*target).getY());

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
	  //adjust velocity if its homing.
	  if((**it).isHoming())
	    {
	      (**it).doHoming(camera.x + mouseX, camera.y + mouseY);
	    }

	  //collision check grunts
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
	  for(std::list<Boomer*>::iterator b = boomers.begin();
	      b != boomers.end(); b++)
	    {
	      if(distForm((**b).getX(), (**b).getY(), (**it).getX(),
			  (**it).getY()) < (**b).getRad() + (**it).getRad())
		{
		  (**b).takeDamage((**it).getDamage());
		  delete *it;
		  bullets.erase(it++);
		  goto end;
		}
	    }
	  for(std::list<Stealth*>::iterator s = stealths.begin();
	      s != stealths.end(); s++)
	    {
	      if(distForm((**s).getX(), (**s).getY(), (**it).getX(),
			  (**it).getY()) < (**s).getRad() + (**it).getRad())
		{
		  (**s).takeDamage((**it).getDamage());
		  delete *it;
		  bullets.erase(it++);
		  goto end;
		}
	    }

	  for(std::list<Carrier*>::iterator c = carriers.begin();
	      c != carriers.end(); c++)
	    {
	      if(distForm((**c).getX(), (**c).getY(), (**it).getX(),
			  (**it).getY()) < (**c).getRad() + (**it).getRad())
		{
		  (**c).takeDamage((**it).getDamage());
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
