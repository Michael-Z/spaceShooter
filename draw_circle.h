//draw_circle.h

#include "SDL/SDL.h"

#ifndef DRAW_CIRCLE_H
#define DRAW_CIRCLE_H

void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

void draw_circle(SDL_Surface *surface, int n_cx, int n_cy, int radius, Uint32 pixel);

#endif
