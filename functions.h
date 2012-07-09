//functions.h

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include "classes.h"

#include <string>
#include <list>

//distance formula
int distForm(int x1, int y1, int x2, int y2);

//unit vector to angle (radians)
double unitToAngle(double x1, double y1);

double angleToUnitX(double angle);
double angleToUnitY(double angle);

//File Loader
SDL_Surface *load_image( std::string filename );

//Surface blitter
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination,
		   SDL_Rect* clip = NULL );

//Initialization
bool init();

//File loading
bool load_files();

//Clean up
void clean_up();

SDL_Surface* rotate(SDL_Surface* source, double angle, double zoom,
                    int smooth);

void renderHUD();

//handle menu input (clicking, mouse location)
void handle_menu_input();

//perform and render units
void doGrunts();
void doBoomers();
void doStealths();
void doCarriers();

void doExplosions();

void gameOver();

#endif
