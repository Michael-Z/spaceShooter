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
		       int sXvel, int sYvel, int dam, int rad, int ran, 
		       bool isHoming)
{
  homing = isHoming;
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

void Projectile::doHoming(int tX, int tY)
{
  int dist = distForm(x, y, tX, tY);

  double x1 = double(tX - x) / dist;
  double y1 = double(tY - y) / dist;

  xVel += int(2 * x1);
  yVel += int(2 * y1);
}

void Projectile::move()
{
  x += xVel / 2;
  y += yVel / 2;
  dist += distForm(0, 0, xVel / 2, yVel / 2);

}

bool Projectile::isOutBounds()
{
  return (x < 0 || y < 0 || x > LEVEL_WIDTH || y > LEVEL_HEIGHT);
}

void Projectile::show()
{//5 is radius of projectile images
  apply_surface(x - camera.x - 5, y - camera.y - 5, picture, screen);
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
