//menus.cpp

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_rotozoom.h"
#include "SDL/SDL_ttf.h"

#include "classes.h"
#include "constants.h"
#include "functions.h"
#include "globals.h"


//watch mouse events and show main menu
void doMainMenu()
{
  //handle inputs for buttons
  if(startGameButton->handle_events())
    isPaused = false;

  //menu background
  apply_surface(0, 0, mainMenuBG, screen);

  //show buttons

  startGameButton->show();
}
