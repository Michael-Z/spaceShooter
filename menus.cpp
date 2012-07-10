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
bool doMainMenu()
{
  //handle inputs for buttons
  if(startGameButton->handle_events())
    isPaused = false;

  if(arcadeModeButton->handle_events())
    printf("Arcade Mode Not yet implemented\n");

  if(loadGameButton->handle_events())
    printf("Load game not yet implemneted\n");

  if(instructionsButton->handle_events())
    menu = 1;

  if(quitGameButton->handle_events())
    return true;

  //menu background
  apply_surface(0, 0, menuBG_1024_768, screen);
  apply_surface(0, 0, mainMenuBG, screen);

  //show buttons

  startGameButton->show();
  arcadeModeButton->show();
  loadGameButton->show();
  instructionsButton->show();
  quitGameButton->show();

  const char* toolTipText = "";

  //check for tool top
  if(startGameButton->inButton(mouseX, mouseY))
    toolTipText = "          Play the regular main game";
  else if(arcadeModeButton->inButton(mouseX, mouseY))
    toolTipText = "    Nonstop action, go for the high score!";
  else if(loadGameButton->inButton(mouseX, mouseY))
    toolTipText = "      Load a previously saved main game";
  else if(instructionsButton->inButton(mouseX, mouseY))
    toolTipText = "               Learn to play the game";
  else if(quitGameButton->inButton(mouseX, mouseY))
    toolTipText = "                   Leave the Game";

  mainMenuToolTip = TTF_RenderText_Solid(font18, toolTipText, font18Color);

  //show button text
  apply_surface(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 4, mainMenuButtonText,
		screen);

  //show tooltips
  apply_surface(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 5, mainMenuToolTip,
		screen);
  
  return false;
}

void instructionsMenu()
{
  if(mainMenuButton->handle_events())
    {
      menu = 0;
      return;
    }

  //apply BG
  apply_surface(0, 0, menuBG_1024_768, screen);
  mainMenuButton->show();
  apply_surface(0, 0, instructionsBG, screen);

  return;
}
