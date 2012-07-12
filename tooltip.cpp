//tooltip.cpp

#include "SDL/SDL.h"

#include "constants.h"
#include "classes.h"
#include "functions.h"
#include "globals.h"

Tooltip::Tooltip(int sX, int sY, int sW, int sH, SDL_Surface* ttImage)
{
  x = sX;
  y = sY;
  w = sW;
  h = sH;
  image = ttImage;
}

bool Tooltip::inTooltip(int tX, int tY)
{
  return ((tX > x) && (tX < (x + w)) && (tY > y) && (tY < (y + h)));
}

void Tooltip::handle_events()
{
  int tx = mouseX; int ty = mouseY;

  if(inTooltip(tx, ty))
    {
      if(ty + image->h > SCREEN_HEIGHT)
	ty -= image->h;
      if(tx + image->w > SCREEN_WIDTH)
	tx -= image->w;
      
      apply_surface(tx, ty, image, screen);
    }
}
