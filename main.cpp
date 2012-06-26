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
  Grunt grunt0 = Grunt(500, 500, &player0);

  //frame rate regulator
  Timer fps;

  if(init() == false)
    return 1;
      
  if(load_files() == false)
    return 1;

  //start frame counter
  frame = 0;

  //while in game
  while(quit == false)
    {
      //start frame timer
      fps.start();
      
      //while events to handle
      while(SDL_PollEvent(&event))
	{
	  //player0 ship movement
	  player0.handle_input();

	  //if user closes window
	  if(event.type == SDL_QUIT)
	    {
	      quit = true;
	    }
	}

      //playerRotated = rotate(player, 30, 1, 0);

      player0.shootBullets();
      player0.moveBullets();
      player0.updateStatusBars();

      player0.accelerate();
      player0.move();
      player0.faceMouse();

      player0.set_camera();

      //background
      apply_surface(0, 0, background, screen, &camera);

      //HUD
      renderHUD();

      //show bullets /* */ should integrate this into move
      player0.showBullets();

      //show player0 on screen
      player0.show();


      //////
      grunt0.accelerate();
      grunt0.move();
      grunt0.shootBullets();
      grunt0.moveBullets();
	
      grunt0.show();

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
