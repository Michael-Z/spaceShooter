#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_rotozoom.h"
#include <string>
#include <math.h>
#include <iostream>

#include "constants.h"
#include "classes.h"
#include "functions.h"
#include "globals.h"

Projectile::Projectile(SDL_Surface* image, int startx, int starty,
		       int sXvel, int sYvel, int dam, int rad, int ran)
{
  picture = image;
  x = startx;
  y = starty;

  damage = dam;
  //velocity = vel;
  radius = rad;
  range = ran;
  dist = 0;

  //xDir and yDir direction unit vector
  xVel = sXvel;
  yVel = sYvel;
}

Projectile::~Projectile()
{
  void(0);
}

void Projectile::move()
{
  x += xVel;
  y += yVel;
  dist += sqrt(pow(xVel, 2) + pow(yVel, 2));

  //std::cout << x << " " << y << " " << dist << std::endl;
}

bool Projectile::isOutBounds()
{
  return (x < 0 || y < 0 || x > LEVEL_WIDTH || y > LEVEL_HEIGHT);
}

void Projectile::show()
{
  apply_surface(x - camera.x, y - camera.y, picture, screen);
}

bool Projectile::collide(int cX, int cY, int rad)
{
  int distance = sqrt((double)(pow(cX - x, 2) + pow(cY - y, 2)));

  return distance <= radius + rad;
}

int Projectile::getDist()
{
  return dist;
}

int Projectile::getRange()
{
  return range;
}

int Projectile::getRad()
{
  return radius;
}

int Projectile::getDamage()
{
  return damage;
}

int Projectile::getX()
{
  return x;
}

int Projectile::getY()
{
  return y;
}
