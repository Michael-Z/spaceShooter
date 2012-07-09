//button.cpp

#include "SDL/SDL.h"

#include "globals.h"
#include "classes.h"
#include "functions.h"

Button::Button(int x, int y, int w, int h, SDL_Rect* buttonClip,
	       SDL_Rect* mouseOverClip, SDL_Rect* buttonClicked)
{
  box.x = x;
  box.y = y;
  box.w = w;
  box.h = h;

  clip = buttonClip;
  mainClip = buttonClip;
  overClip = mouseOverClip;
  clicked = buttonClicked;
}

bool Button::inButton(int x, int y)
{
  return ((x > box.x) && (x < box.x + box.w) && (y > box.y) && 
	  (y < box.y + box.h));

}

bool Button::handle_events()
{
  int x = mouseX; int y = mouseY;
  
  if(event.type == SDL_MOUSEBUTTONDOWN)
    {
      if(event.button.button == SDL_BUTTON_LEFT)
	{
	  if(inButton(x, y))
	    {
	      clip = clicked;
	    }
	}
    }
  else if(event.type == SDL_MOUSEBUTTONUP)
    {
      if(event.button.button == SDL_BUTTON_LEFT)
	{
	  //if in button return true, execute button action
	  if(clip == clicked && inButton(x, y))
	    return true;
	}
    }
  else if(clip == clicked && inButton(x, y))
    return false;

  else
    {
      //change color if mouse is over clip
      if(inButton(x, y))
	{
	  clip = overClip;
	}
      else
	clip = mainClip;
    }
  
  //default behavior, do not perform button action
  return false;
}

void Button::show()
{
  apply_surface(box.x, box.y, mainMenuButtons, screen, clip);
}
