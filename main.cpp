/* SpaceShooter (name tbd) by Bailey Forrest bcforres@andrew.cmu.edu */

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "constants.h"
#include "classes.h"
#include "functions.h"
#include "globals.h"

#include <iostream>
#include <list>

int main(int argc, char* args[])
{
  //quit flag
  bool quit = false;

  //the player
  Player player0;

  //frame rate regulator
  Timer fps;

  if(init() == false)
    return 1;
      
  if(load_files() == false)
    return 1;

  //start frame counter
  frame = 0;

  //create enemy lists
  std::list<Grunt*> grunts;
  grunts.push_back(new Grunt(500, 500, &player0));
  grunts.push_back(new Grunt(1500, 500, &player0));
  grunts.push_back(new Grunt(500, 1500, &player0));
  grunts.push_back(new Grunt(1500, 1500, &player0));

  //while in game
  while(quit == false)
    {
      //start frame timer
      fps.start();
      
      //while events to handle
      while(SDL_PollEvent(&event))
	{
	  //player0 ship movement/ shooting
	  player0.handle_input();

	  //if user closes window
	  if(event.type == SDL_QUIT)
	    {
	      quit = true;
	    }
	}

      //background
      apply_surface(0, 0, background, screen, &camera);

      //HUD
      renderHUD();

      player0.doUnit();
      
      doGrunts(grunts);

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
