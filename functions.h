//functions.h

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"


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
SDL_Surface *load_image(const char* filename, bool transparent = false );

//Surface blitter
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination,
		   SDL_Rect* clip = NULL );

//Initialization
bool init();

//File loading
bool load_files();

//create objects
void setButtons_and_Frames();
void create_Tooltips();


//Clean up
void clean_up();

SDL_Surface* rotate(SDL_Surface* source, double angle, double zoom,
                    int smooth);

void renderHUD(Player *player);

//perform and render units
void doGrunts();
void doBoomers();
void doStealths();
void doCarriers();

void doExplosions();

void gameOver();

void showText(const char* text, TTF_Font *font, SDL_Color color, int x, int y);

const char* intToString(int i);

void resetEnemies();

void playSound(Mix_Chunk *sound);

void setMainMessage(const char *message, int time);

void increaseDifficulty();

//init.cpp functions

void reset();

//arcadeMode.cpp functions
void doArcadeMode(Player *player0);

//mainGame.cpp functions
void doMainGame(Player *player0);
void doWave1(Player *player0);
void doWave2(Player *player0);
void doWave3(Player *player0);
void doWave4(Player *player0);
void doWave5(Player *player0);
void doWave6(Player *player0);
void doWave7(Player *player0);
void doWave8(Player *player0);

#endif
