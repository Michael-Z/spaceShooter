//menus.cpp

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_rotozoom.h"
#include "SDL/SDL_ttf.h"

#include <sstream>

#include "classes.h"
#include "constants.h"
#include "functions.h"
#include "globals.h"
#include "menus.h"

bool handle_menu_input()
{
  if(event.type == SDL_MOUSEMOTION)
    {
      mouseX = event.motion.x;
      mouseY = event.motion.y;
    }
  if(event.type == SDL_KEYDOWN)
    switch(event.key.keysym.sym)
      {
      case SDLK_ESCAPE:
	switch(menu)
	  {
	  case 0: return true; break;
	  case 1: menu = 0; break;
	  case 2: isPaused = false; break;
	  case 3: menu = 2; break;
	  default: menu = 2; break;
	  }
      default: void(); break;
      }
  return false;
}


//watch mouse events and show main menu
bool doMainMenu()
{
  //handle inputs for buttons
  if(startGameButton->handle_events())
    {
      gameMode = 0;
      isPaused = false;
    }

  if(arcadeModeButton->handle_events())
    {
      gameMode = 1;
      isPaused = false;
    }

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
    toolTipText = "Play the regular main game";
  else if(arcadeModeButton->inButton(mouseX, mouseY))
    toolTipText = "Nonstop action, go for the high score!";
  else if(loadGameButton->inButton(mouseX, mouseY))
    toolTipText = "Load a previously saved main game";
  else if(instructionsButton->inButton(mouseX, mouseY))
    toolTipText = "Learn to play the game";
  else if(quitGameButton->inButton(mouseX, mouseY))
    toolTipText = "Leave the Game";

  mainMenuToolTip = TTF_RenderText_Solid(font18, toolTipText, font18Color);

  //show button text
  apply_surface(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 4, mainMenuButtonText,
		screen);

  int width;
  if(mainMenuToolTip == NULL)
    width = 0;
  else
    width = mainMenuToolTip->w;
  

  //show tooltips
  apply_surface((SCREEN_WIDTH - width) / 2, SCREEN_HEIGHT / 5,
		mainMenuToolTip, screen);
  
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

void doPauseMenu()
{
  if(resumeGameButton->handle_events())
    {
      isPaused = false;
    }
  if(skillMenuButton->handle_events())
    {
      menu = 3;
    }
  if(saveGameButton->handle_events())
    {
      printf("Save Game\n");
      //saveGame();
    }
  if(mainMenuButton->handle_events())
    {
      menu = 0;
    }

  //pause menu background
  apply_surface(0, 0, menuBG_1024_768, screen);

  //show buttons
  resumeGameButton->show();
  skillMenuButton->show();
  saveGameButton->show();
  mainMenuButton->show();

  apply_surface(0, 0, pauseMenuBG, screen);
}

void doSkillMenu(Player* player)
{
  const char* title;

  apply_surface(0, 0, menuBG_1024_768, screen);

  if(offensiveTreeButton->handle_events())
    {
      skillTree = 0;
    }
  else if(defensiveTreeButton->handle_events())
    skillTree = 1;
  else if(abilityTreeButton->handle_events())
    skillTree = 2;
  else if(pauseMenuButton->handle_events())
    {
      menu = 2;
      return;
    }

  switch(skillTree)
    {
    case 0: doOffensiveTree(player); title = "Offensive Skills"; break;
    case 1: doDefensiveTree(player); title = "Defensive Skills"; break;
    case 2: doAbilityTree(player); title = "Ability Skills"; break;
    default: doOffensiveTree(player);
    }

  SDL_Surface *skillTreeTitle = TTF_RenderText_Solid(font28, title,
						     font28Color);

  apply_surface((SCREEN_WIDTH - skillTreeTitle->w) / 2, 30,
		skillTreeTitle, screen);

  SDL_FreeSurface(skillTreeTitle);


  SDL_Color red = { 255, 0, 0 };

  std::stringstream skillPointAmount;

  skillPointAmount << "Free Tech Points: " << player->getSkillPoints();

  SDL_Surface *skillPointsLabel =
    TTF_RenderText_Solid(font18, skillPointAmount.str().c_str(), red);

  apply_surface(40, 120, skillPointsLabel, screen);

  SDL_FreeSurface(skillPointsLabel);

  //show buttons
  offensiveTreeButton->show();
  defensiveTreeButton->show();
  abilityTreeButton->show();
  pauseMenuButton->show();

  apply_surface(0, 0, skillTreeBG, screen);
}

void doOffensiveTree(Player* player)
{
  apply_surface(0, 0, offensiveTreeBG, screen);

  //MS buttons
  if(MS_damageButton->handle_events(player->MS_damagePoints))
    {
      if(player->useSkillPoint())
	{
	  player->MS_damagePoints++;
	  player->MS_damage += 3;
	}
    }
  if(player->getLevel() >= 3 && player->MS_damagePoints > 0)
    {
      if(MS_rangeButton->handle_events(player->MS_rangePoints)
	 && player->useSkillPoint())
	{
	  player->MS_rangePoints++;
	  player->MS_range += 50;
	}
    }
  else
    MS_rangeButton->skillUnavail();

  if(player->getLevel() >= 5 && player->MS_rangePoints > 0)
    {
      if(MS_radiusButton->handle_events(player->MS_radiusPoints)
	 && player->useSkillPoint())
	{
	  player->MS_radiusPoints++;
	  player->MS_radius += 2;
	}
    }
  else
    MS_radiusButton->skillUnavail();

  if(player->getLevel() >= 10 && player->MS_radiusPoints > 0)
    {
      if(MS_rateButton->handle_events(player->MS_ratePoints)
	 && player->MS_ratePoints < 1 && player->useSkillPoint())
	{
	  player->MS_ratePoints++;
	  player->MS_rate /= 2;
	}
    }
  else
    MS_rateButton->skillUnavail();

  //MG buttons
  if(MG_damageButton->handle_events(player->MG_damagePoints))
    {
      if(player->useSkillPoint())
	{
	  player->MG_damagePoints++;
	  player->MG_damage += 1;
	}
    }

  if(player->getLevel() >= 3 && player->MG_damagePoints > 0)
    {
      if(MG_speedButton->handle_events(player->MG_speedPoints) &&
	 player->MG_speedPoints < 5 && player->useSkillPoint())
	{
	  player->MG_speedPoints++;
	  player->MG_speed += 2;
	}
    }
  else
    MG_speedButton->skillUnavail();

  if(player->getLevel() >= 5 && player->MG_speedPoints > 0)
    {
      if(MG_rangeButton->handle_events(player->MG_rangePoints) &&
	 player->useSkillPoint())
	{
	  player->MG_rangePoints++;
	  player->MG_range += 25;
	}
    }
  else
    MG_rangeButton->skillUnavail();

  //gives two shots
  if(player->getLevel() >= 10 && player->MG_rangePoints > 0)
    {
      if(MG_doubleButton->handle_events(player->MG_doublePoints) &&
	 player->MG_doublePoints < 1 && player->useSkillPoint())
	{
	  player->MG_doublePoints++;
	  player->MG_double = true;
	}
    }
  else
    MG_doubleButton->skillUnavail();

  //SG buttons
  if(SG_rangeButton->handle_events(player->SG_rangePoints))
    {
      if(player->useSkillPoint())
	{
	  player->SG_rangePoints++;
	  player->SG_range += 25;
	}
    }

  if(player->getLevel() >= 3 && player->SG_rangePoints > 0)
    {
      if(SG_damageButton->handle_events(player->SG_damagePoints) &&
	 player->useSkillPoint())
	{
	  player->SG_damagePoints++;
	  player->SG_damage += 1;
	}
    }
  else
    SG_damageButton->skillUnavail();

  if(player->getLevel() >= 5 && player->SG_damagePoints > 0)
    {
      if(SG_rateButton->handle_events(player->SG_ratePoints) &&
	 player->SG_ratePoints < 7 && player->useSkillPoint())
	{
	  player->SG_ratePoints++;
	  player->SG_rate -= 2;
	}
    }
  else
    SG_rateButton->skillUnavail();

  //doubles pellets
  if(player->getLevel() >= 10 && player->SG_ratePoints > 0)
    {
      if(SG_doubleButton->handle_events(player->SG_doublePoints) &&
	 player->SG_doublePoints < 1 && player->useSkillPoint())
	{
	  player->SG_doublePoints++;
	  player->SG_double = true;
	}
    }
  else
    SG_doubleButton->skillUnavail();

  //HM
  if(HM_rangeButton->handle_events(player->HM_rangePoints))
    {
      if(player->useSkillPoint())
	{
	  player->HM_rangePoints++;
	  player->homing_range += 50;
	}
    }

  if(player->getLevel() >= 3 && player->HM_rangePoints > 0)
    {
      if(HM_damageButton->handle_events(player->HM_damagePoints) &&
	 player->useSkillPoint())
	{
	  player->HM_damagePoints++;
	  player->homing_damage += 2;
	}
    }
  else
    HM_damageButton->skillUnavail();

  if(player->getLevel() >= 5 && player->HM_damagePoints > 0)
    {
      if(HM_radiusButton->handle_events(player->HM_radiusPoints) &&
	 player->useSkillPoint())
	{
	  player->HM_radiusPoints++;
	  player->homing_radius += 2;
	}
    }
  else
    HM_radiusButton->skillUnavail();

  //shoot 4 HM
  if(player->getLevel() >= 10 && player->HM_radiusPoints > 0)
    {
      if(HM_doubleButton->handle_events(player->HM_doublePoints) &&
	 player->HM_doublePoints < 1 && player->useSkillPoint())
	{
	  player->HM_doublePoints++;
	  player->HM_double = true;
	}
    }
  else
    HM_doubleButton->skillUnavail();

  MS_damageButton->handle_tooltip();
  MS_rangeButton->handle_tooltip();
  MS_radiusButton->handle_tooltip();
  MS_rateButton->handle_tooltip();

  MG_damageButton->handle_tooltip();
  MG_speedButton->handle_tooltip();
  MG_rangeButton->handle_tooltip();
  MG_doubleButton->handle_tooltip();

  SG_rangeButton->handle_tooltip();
  SG_damageButton->handle_tooltip();
  SG_rateButton->handle_tooltip();
  SG_doubleButton->handle_tooltip();

  HM_rangeButton->handle_tooltip();
  HM_damageButton->handle_tooltip();
  HM_radiusButton->handle_tooltip();
  HM_doubleButton->handle_tooltip();
}

void doDefensiveTree(Player* player)
{
  apply_surface(0, 0, defensiveTreeBG, screen);
}

void doAbilityTree(Player* player)
{
  apply_surface(0, 0, abilityTreeBG, screen);
}
