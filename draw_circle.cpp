/* draw_circle.cpp
from http://content.gpwiki.org/index.php/SDL:Tutorials:Drawing_and_Filling_Circles

*/

//modified to prevent segfaults from out of screen drawing

#include "constants.h"
#include "SDL/SDL.h"

void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel) {
  if(x > 0 && y > 0 && x < SCREEN_WIDTH && y < SCREEN_HEIGHT)
    {
      Uint8 *target_pixel = (Uint8 *)surface->pixels + y * surface->pitch +
	x * 4;
      *(Uint32 *)target_pixel = pixel;
    }
}

void draw_circle(SDL_Surface *surface, int n_cx, int n_cy, int radius, Uint32 pixel) {
  // if the first pixel in the screen is represented by (0,0) (which is in sdl)
  // remember that the beginning of the circle is not in the middle of the pixel
  // but to the left-top from it:
  double error = (double)-radius;
  double x = (double)radius -0.5;
  double y = (double)0.5;
  double cx = n_cx - 0.5;
  double cy = n_cy - 0.5;

  while (x >= y)
    {
      set_pixel(surface, (int)(cx + x), (int)(cy + y), pixel);
      set_pixel(surface, (int)(cx + y), (int)(cy + x), pixel);
          
      if (x != 0)
	{
	  set_pixel(surface, (int)(cx - x), (int)(cy + y), pixel);
	  set_pixel(surface, (int)(cx + y), (int)(cy - x), pixel);
	}
      
      if (y != 0)
	{
	  set_pixel(surface, (int)(cx + x), (int)(cy - y), pixel);
	  set_pixel(surface, (int)(cx - y), (int)(cy + x), pixel);
	}
      
      if (x != 0 && y != 0)
	{
	  set_pixel(surface, (int)(cx - x), (int)(cy - y), pixel);
	  set_pixel(surface, (int)(cx - y), (int)(cy - x), pixel);
	}

      error += y;
      ++y;
      error += y;

      if (error >= 0)
	{
	  --x;
	  error -= x;
	  error -= x;
	}
    }
}

