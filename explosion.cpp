//explosion.cpp

#include "classes.h"
#include "globals.h"
#include "functions.h"

Explosion::Explosion(int sX, int sY)
{
  stage = 0;
  x = sX;
  y = sY;
}

int Explosion::get_stage()
{
  return stage;
}

void Explosion::show()
{
  apply_surface(x - camera.x - 32, y - camera.y - 32, explosion, screen,
		&explosion_frames[stage]);
  stage++;
  if(stage > 24) stage = 0; // shouldn't get here
}
