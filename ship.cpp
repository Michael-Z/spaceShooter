//ship.cpp

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_rotozoom.h"
#include <string>
#include <list>
#include <iostream>

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
      takeDamage(abs(xVel) * 4);
      xVel = -xVel / 2; //ricochet
    }
    
  //Move the ship up or down
  y += yVel;
    
  //If the ship went too far up or down
  if( ( y < SHIP_HEIGHT / 2 ) || ( y + SHIP_HEIGHT > LEVEL_HEIGHT ) )
    {
      //move back
      y -= yVel;
      takeDamage(abs(yVel) * 4);
      yVel = -yVel / 2;
    }
}

void Ship::show()
{
  //Show the ship
  apply_surface( x, y, player, screen );
}

void Ship::takeDamage(int damage)
{
  if(shield - damage > 0)
    shield -= damage;
  else
    {
      damage -= shield;
      shield = 0;

      if(armor - damage > 0)
	armor -= damage;
      else
	{
	  damage -= armor;
	  armor = 0;
	  
	  if(hull - damage > 0)
	      hull -= damage;
	  else
	    {
	      hull = 0;
	      gameOver();
	    }
	}
	  
    }
}
