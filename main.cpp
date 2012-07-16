/* SpaceShooter (name tbd) by Bailey Forrest bcforres@andrew.cmu.edu */

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include "constants.h"
#include "classes.h"
#include "functions.h"
#include "globals.h"
#include "menus.h"

#include <iostream>
#include <list>

int main(int argc, char* args[])
{
  //quit flag
  bool quit = false;

  //frame rate regulator
  Timer fps;

  if(init() == false)
    return 1;
      
  if(load_files() == false)
    return 1;

  setButtons_and_Frames();
  create_Tooltips();

  //start frame counter
  frame = 0;

  //play music
  //Mix_PlayMusic(mainMusic, -1);

  //the player
  Player *player0 = NULL;

  //while in game
  while(quit == false)
    {
      //start frame timer
      fps.start();
      
      //while events to handle
      while(SDL_PollEvent(&event))
	{
	  //player0 ship movement/ shooting
	  if(isPaused == false)
	     player0->handle_input();
	  else
	    quit = handle_menu_input();

	  //if user closes window
	  if(event.type == SDL_QUIT)
	    {
	      quit = true;
	    }
	}

      if(isPaused == false)
	{
	  //background
	  apply_surface(0, 0, background, screen, &camera);

	  if(gameMode == 0)
	    {
	      doMainGame(player0);
	    }

	  else if(gameMode == 1)
	    doArcadeMode(player0);

	  //control units
	  player0->doUnit();
	  doGrunts();
	  doBoomers();
	  doStealths();
	  doCarriers();
	  
	  doExplosions();
	  
	  //HUD
	  renderHUD(player0);
	}
      else if(quit == false) //paused, show some sort of menu;
	{
	  switch(menu) //show menu based on menu variable
	    {
	    case 0:
	      quit = doMainMenu();
	      //going to mainMenu, reset everything
	      if(player0 != NULL)
		delete player0;
	      player0 = new Player;
	      reset();
	      break;
	    case 1: instructionsMenu(); break;
	    case 2: doPauseMenu(); break;
	    case 3: doSkillMenu(player0); break;
	      //case 4: doShopMenu(player0); break;
	      //if not valid menu, unpause game
	    default: isPaused = false;
	    }
	}
      
      //update screen
      if(SDL_Flip(screen) == -1)
	return 1;

      //cap frame rate
      if(fps.get_ticks() < 1000 / FRAMES_PER_SECOND)
	{
	  SDL_Delay((1000 / FRAMES_PER_SECOND) - fps.get_ticks());
	}
	
      frame++;
    }

  clean_up();

  return 0;
}
