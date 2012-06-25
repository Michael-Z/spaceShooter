//ship.cpp

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_rotozoom.h"
#include <string>
#include <list>

#include "constants.h"
#include "classes.h"
#include "functions.h"
#include "globals.h"

Ship::Ship()
{
  //Initialize the offsets
  x = 0;
  y = 0;
    
  //Initialize the velocity
  xVel = 0;
  yVel = 0;

  //initialize the image of the ship
}

void Ship::move()
{
  //Move the ship left or right
  x += xVel;
    
  //If the ship went too far to the left or right
  if( ( x < SHIP_HEIGHT / 2 ) || ( x + SHIP_WIDTH > LEVEL_WIDTH ) )
    {
      //move back
      x -= xVel;
      xVel = -xVel / 2; //ricochet
    }
    
  //Move the ship up or down
  y += yVel;
    
  //If the ship went too far up or down
  if( ( y < SHIP_HEIGHT / 2 ) || ( y + SHIP_HEIGHT > LEVEL_HEIGHT ) )
    {
      //move back
      y -= yVel;
      yVel = -yVel / 2;
    }
}

void Ship::show()
{
  //Show the ship
  apply_surface( x, y, player, screen );
}
