//mainGame.cpp - controls how the waves and main game will go.

#include "SDL/SDL_ttf.h"

#include <sstream>
#include "globals.h"
#include "functions.h"

void doMainGame(Player *player0)
{
  if(!inWave) //starting a new wave
    {
      waveStage = -1;
      waveStartFrame = frame;
      currentWave++;
      std::stringstream waveText;
      waveText << "Wave " << currentWave;
      mainMessage = TTF_RenderText_Solid(font28, waveText.str().c_str(),
					 font28Color);
      mainMessageTimer = 60;
      inWave = true;
    }

  switch(currentWave)
    {
    case 1: doWave1(player0); break;
    case 2: doWave2(player0); break;

    default: printf("you win!\n"); menu = 0; isPaused = true; break;
    }

}

void doWave1(Player *player0)
{
  if(frame - waveStartFrame == 80)
    {
      mainMessage = TTF_RenderText_Solid(font28, "Keep moving...otherwise"
					 " you're dead...", font28Color);
      mainMessageTimer = 60;      
    }

  //defeated all enemies, move on to the next stage
  if(grunts.size() == 0 && waveCount == 0)
    waveStage++;
  else if(waveCount != 0)
    void();
  else
    return;

  switch(waveStage)
    {
    case 0:
	grunts.push_back(new Grunt(500, 500, player0));
	break;

    case 1:
      grunts.push_back(new Grunt(500, 1000, player0));
      grunts.push_back(new Grunt(1500, 1000, player0));
      break;

    case 2:
      grunts.push_back(new Grunt(1500, 1500, player0));
      grunts.push_back(new Grunt(500, 500, player0));
      grunts.push_back(new Grunt(1500, 500, player0));
      grunts.push_back(new Grunt(500, 1000, player0));
      break;

    case 3:
      if(waveCount == 0)
	waveCount = 20;

      if(frame % 320 == 0 || grunts.size() == 0)
	{
	  if(frame % 640 == 0)
	    {
	      grunts.push_back(new Grunt(500, 500, player0));
	      grunts.push_back(new Grunt(1500, 1500, player0));
	    }
	  else
	    {
	      grunts.push_back(new Grunt(1500, 500, player0));
	      grunts.push_back(new Grunt(500, 1500, player0));
	    }

	  waveCount -= 2;
	}
      break;
      
    default:
      inWave = false;
      break;
      
    }
}

void doWave2(Player *player0)
{
  if(frame - waveStartFrame == 80)
    {
      mainMessage = TTF_RenderText_Solid(font28, "You better dodge this...",
					 font28Color);
      mainMessageTimer = 60;
    }
  
  if(grunts.size() == 0 && waveCount == 0)
    waveStage++;
  else if(waveCount != 0)
    void();
  else
    return;

  switch(waveStage)
    {
    case 0:
      grunts.push_back(new Grunt(500, 500, player0));
      boomers.push_back(new Boomer(200, 200, player0));
      boomers.push_back(new Boomer(1800, 1800, player0));
      boomers.push_back(new Boomer(1800, 200, player0));
      boomers.push_back(new Boomer(200, 1800, player0));
      break;

    case 1:
      grunts.push_back(new Grunt(1000, 200, player0));
      grunts.push_back(new Grunt(200, 1000, player0));
      grunts.push_back(new Grunt(1800, 1000, player0));
      grunts.push_back(new Grunt(1000, 1800, player0));

      boomers.push_back(new Boomer(500, 1500, player0));
      boomers.push_back(new Boomer(1500, 500, player0));
      boomers.push_back(new Boomer(500, 500, player0));
      boomers.push_back(new Boomer(1500, 1500, player0));
      break;

    case 2:
      if(waveCount == 0)
	waveCount = 20;

      if(frame % 320 == 0 || grunts.size() == 0)
        {
          if(frame % 640 == 0)
            {
              grunts.push_back(new Grunt(500, 500, player0));
              grunts.push_back(new Grunt(1500, 1500, player0));
            }
          else
            {
              grunts.push_back(new Grunt(1500, 500, player0));
              grunts.push_back(new Grunt(500, 1500, player0));
            }

          waveCount -= 2;
        }

      if(frame % 120 == 0)
	{
	  boomers.push_back(new Boomer(1000, 200, player0));
	  boomers.push_back(new Boomer(1000, 1800, player0));
	}
      break;

    default: inWave = false;
    }

}
