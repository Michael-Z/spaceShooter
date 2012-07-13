//button.cpp

#include "SDL/SDL.h"

#include "globals.h"
#include "classes.h"
#include "functions.h"

Button::Button(int x, int y, int w, int h, SDL_Surface *theButtonSheet,
	       SDL_Rect* buttonClip,
	       SDL_Rect* mouseOverClip, SDL_Rect* buttonClicked)
{
  box.x = x;
  box.y = y;
  box.w = w;
  box.h = h;

  buttonSheet = theButtonSheet;
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
	    {
	      clip = overClip;
	      return true;
	    }
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
  apply_surface(box.x, box.y, buttonSheet, screen, clip);
}


//skill Button 
Skill::Skill(int tx, int ty, int tw, int th, int reqlevel,
	     SDL_Surface* tooltipImg, Skill* reqPrerequesite)
{
  x = tx;
  y = ty;
  w = tw;
  h = th;
  level = reqlevel;
  prerequesite = reqPrerequesite;
  points = 0;

  button = new Button(x, y, w, h, skillButtonSelection, 
		      &skillButtonSelectionFrames[0],
		      &skillButtonSelectionFrames[1],
		      &skillButtonSelectionFrames[2]);
  
  tooltip = new Tooltip(x, y, w, h, tooltipImg);

}

bool Skill::handleEvents(Player *player0)
{
  bool returnVal;
  if(player0->getLevel() >= level && prerequesite->points > 0)
    {
      if(button->handle_events() && player0->useSkillPoint())
	{
	  points++;
	  returnVal = true;
	}
    }
  else
    {
      apply_surface(x, y, skillUnavailable, screen);
      returnVal = false;
    }
  
  button->show();

  SDL_Color color = { 0xAA, 0xAA, 0xAA };

  showText(intToString(points), font18, color, x, y);
  tooltip->handle_events();
  
  return returnVal;
}
