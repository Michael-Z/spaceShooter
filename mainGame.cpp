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
      waveCount = 0;
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
    case 3: doWave3(player0); break;
    case 4: doWave4(player0); break;
    case 5: doWave5(player0); break;
    case 6: doWave6(player0); break;

    default: menu = 6; isPaused = true; break;
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

      if(frame % 120 == 0 && waveCount> 2)
	{
	  boomers.push_back(new Boomer(1000, 200, player0));
	  boomers.push_back(new Boomer(1000, 1800, player0));
	}
      break;

    default: inWave = false;
    }
}

void doWave3(Player *player0)
{
  if(frame - waveStartFrame == 80)
    {
      mainMessage = TTF_RenderText_Solid(font28, "RUN FOR IT!", font28Color);
      mainMessageTimer = 60;
    }
  
  if(frame - waveStartFrame == 0)
    {
      waveCount = 10;
      return;
    }

  if(boomers.size() == 0 && waveCount == 0)
    inWave = false;
  if(waveCount == 0)
    return;

  if((frame - waveStartFrame) % 200 == 0)
    {
      for(int i = 400; i < 2000; i += 400)
	{
	  for(int j = 400; j < 2000; j+= 400)
	    {
	      boomers.push_back(new Boomer(i, j, player0));
	    }
	}
      waveCount--;
    }
}

void doWave4(Player *player0)
{
  if(frame - waveStartFrame == 80)
    {
      setMainMessage("Keep your eyes open for this one", 60);
    }
  
  if(grunts.size() == 0 && waveCount == 0 && stealths.size() == 0)
    waveStage++;
  else if(waveCount != 0)
    void();
  else
    return;

  switch(waveStage)
    {
    case 0:
      for(int i = 100; i < 2000; i += 1800)
	for(int j = 100; j < 2000; j += 400)
	  {
	    grunts.push_back(new Grunt(i, j, player0));
	    grunts.push_back(new Grunt(j, i, player0));
	  }
      break;

    case 1:
      if(waveCount == 0)
	{
	  waveCount = 10;
	  stealths.push_back(new Stealth(1000, 1000, player0));
	  stealths.push_back(new Stealth(1500, 1500, player0));
	}

      if(frame % 320 == 0 || (grunts.size() == 0 && boomers.size() == 0))
	{
	  grunts.push_back(new Grunt(200, 1000, player0));
	  grunts.push_back(new Grunt(1800, 1000, player0));
	  grunts.push_back(new Grunt(1000, 200, player0));
	  grunts.push_back(new Grunt(1000, 1800, player0));
      
	  boomers.push_back(new Boomer(1900, 1900, player0));
	  boomers.push_back(new Boomer(100, 100, player0));
	  waveCount--;
	}
      break;

    case 2:
      {
	stealths.push_back(new Stealth(500, 500, player0));
	stealths.push_back(new Stealth(1500, 500, player0));
	stealths.push_back(new Stealth(500, 1500, player0));
	stealths.push_back(new Stealth(1500, 1500, player0));

	break;
      }
			   
    default: inWave = false; break;
    }
}

void doWave5(Player *player0)
{
  int waveTime = frame - waveStartFrame;
  if(waveTime == 80)
    setMainMessage("Uh... just don't die!... 60 seconds!", 60);

  if(waveTime < 40 * 60) //survive one minute
    {
      if(waveTime < 40 * 15) // first 15 seconds
	{
	  if(waveTime % 40 == 0)
	    {
	      boomers.push_back(new Boomer((waveTime % 200) * 10, 100,
					   player0));
	    }
	  if(waveTime % 160 == 0)
	    {
	      grunts.push_back(new Grunt(200, 1800, player0));
	      grunts.push_back(new Grunt(800, 1800, player0));
	      grunts.push_back(new Grunt(1600, 1800, player0));
	      grunts.push_back(new Grunt(1800, 1800, player0));
	    }
	}
      else if(waveTime < 40 * 30) //next 15 seconds
	{
	  if(waveTime % 20 == 0)
	    {
	      boomers.push_back(new Boomer(100,(waveTime % 200) * 10,
					   player0));
	    }
	  if(waveTime % 320 == 0)
	    {
	      grunts.push_back(new Grunt(200, 1800, player0));
	      grunts.push_back(new Grunt(800, 1800, player0));
	      grunts.push_back(new Grunt(1600, 1800, player0));
	      grunts.push_back(new Grunt(1800, 1800, player0));

	      grunts.push_back(new Grunt(200, 100, player0));
	      grunts.push_back(new Grunt(800, 100, player0));
	      grunts.push_back(new Grunt(1600, 100, player0));
	      grunts.push_back(new Grunt(1800, 100, player0));
	    }

	}
      else if(waveTime < 40 * 45) //3rd 15 seconds
	{
	  if(waveTime % 20 == 0)
	    {
	      boomers.push_back(new Boomer(1900,(waveTime % 200) * 10,
					   player0));
	    }
	  if(waveTime % 320 == 0)
	    {
	      grunts.push_back(new Grunt(200, 1800, player0));
	      grunts.push_back(new Grunt(800, 1800, player0));
	      grunts.push_back(new Grunt(1600, 1800, player0));
	      grunts.push_back(new Grunt(1800, 1800, player0));

	      grunts.push_back(new Grunt(200, 100, player0));
	      grunts.push_back(new Grunt(800, 100, player0));
	      grunts.push_back(new Grunt(1600, 100, player0));
	      grunts.push_back(new Grunt(1800, 100, player0));
	    }

	  if(waveTime % 320 == 0)
	    {
	      stealths.push_back(new Stealth(1000, 1000, player0));
	    }
	  
	}
      else //last 15 seconds
	{
	  if(waveTime % 10 == 0)
	    {
	      boomers.push_back(new Boomer(1900,(waveTime % 200) * 10,
					   player0));

	      boomers.push_back(new Boomer(100, 2000 - (waveTime % 200) * 10,
					   player0));
	    }

	  if(waveTime % 160 == 0)
	    {
	      grunts.push_back(new Grunt(200, 1800, player0));
	      grunts.push_back(new Grunt(800, 1800, player0));
	      grunts.push_back(new Grunt(1600, 1800, player0));
	      grunts.push_back(new Grunt(1800, 1800, player0));

	      grunts.push_back(new Grunt(200, 100, player0));
	      grunts.push_back(new Grunt(800, 100, player0));
	      grunts.push_back(new Grunt(1600, 100, player0));
	      grunts.push_back(new Grunt(1800, 100, player0));

	      stealths.push_back(new Stealth(500, 500, player0));
	      stealths.push_back(new Stealth(1500, 1500, player0));
	    }
	}
    }
  if(waveTime > 40 * 60 && grunts.size() == 0 && boomers.size() == 0 &&
     stealths.size() == 0)
    inWave = false;
}

void doWave6(Player *player0)
{
  int waveTime = frame - waveStartFrame;

  if(waveTime == 0)
    {
      waveCount = 10;
      return;
    }

  if(grunts.size() == 0 && waveCount == 0)
    inWave = false;
  if(waveCount == 0)
    return;

  if((waveTime % 200) == 0)
    {
      for(int i = 400; i < 2000; i += 400)
        {
          for(int j = 400; j < 2000; j+= 400)
            {
              grunts.push_back(new Grunt(i, j, player0));
            }
        }
      waveCount--;
    }


}
