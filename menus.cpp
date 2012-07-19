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

void gameOverMenu()
{
  if(mainMenuButton->handle_events())
    {
      menu = 0;
      return;
    }

  //apply BG
  apply_surface(0, 0, menuBG_1024_768, screen);
  mainMenuButton->show();
  apply_surface(0, 0, gameOverBG, screen);

  return;
}

void victoryMenu()
{
  if(mainMenuButton->handle_events())
    {
      menu = 0;
      return;
    }

  apply_surface(0, 0, menuBG_1024_768, screen);
  mainMenuButton->show();

  apply_surface(0, 0, victoryBG, screen);

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

  //show buttons
  offensiveTreeButton->show();
  defensiveTreeButton->show();
  abilityTreeButton->show();
  pauseMenuButton->show();

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

  if(shieldAmountButton->handle_events(player->shieldAmountPoints) &&
     player->useSkillPoint())
    {
      player->shieldAmountPoints++;
      player->shield += player->level * SHIELD_PER_POINT;
      player->maxShield += player->level * SHIELD_PER_POINT;
    }

  if(player->level >= 3 && player->shieldAmountPoints > 0)
    {
      if(shieldRegenButton->handle_events(player->shieldRegenPoints) &&
	 player->useSkillPoint())
	{
	  player->shieldRegenPoints++;
	  if(player->shieldRegenPoints % 2 == 0)
	    player->shieldRegen++;
	  
	}
    }
  else
    shieldRegenButton->skillUnavail();

  if(player->level >= 5 && player->shieldRegenPoints > 0)
    {
      if(shieldCapButton->handle_events(player->shieldCapPoints) &&
	 player->shieldCapPoints < 1 && player->useSkillPoint())
	{
	  player->shieldCapPoints++;
	  player->shieldCap = true;
	}
    }
  else
    shieldCapButton->skillUnavail();

  if(armorAmountButton->handle_events(player->armorAmountPoints) &&
     player->useSkillPoint())
    {
      player->armorAmountPoints++;
      player->maxArmor += player->level * ARMOR_PER_POINT;
      player->armor += player->level * ARMOR_PER_POINT;
    }

  if(player->level > 3 && player->armorAmountPoints > 0)
    {
      if(hullAmountButton->handle_events(player->hullAmountPoints) &&
	 player->useSkillPoint())
	{
	  player->hullAmountPoints++;
	  player->maxHull += player->level * HULL_PER_POINT;
	  player->hull += player->level * HULL_PER_POINT;
	}
    }
  else
    hullAmountButton->skillUnavail();

  if(player->level >= 3 && player->shieldAmountPoints > 0 &&
     player->armorAmountPoints > 0)
    {
      if(evasionButton->handle_events(player->evasionPoints) &&
	 player->evasionPoints < 10 && player->useSkillPoint())
	{
	  player->evasionPoints++;
	  player->evasion += 4;
	}
    }
  else
    evasionButton->skillUnavail();

  if(player->level >= 5 && player->evasionPoints > 0 &&
     player->shieldRegenPoints > 0 && player->hullAmountPoints > 0)
    {
      if(hitRadButton->handle_events(player->hitRadPoints) &&
	 player->hitRadPoints < 5 && player->useSkillPoint())
	{
	  player->hitRadPoints++;
	  player->hitRadius -= 2;
	}
    }
  else
    hitRadButton->skillUnavail();

  if(player->level >= 10 && player->hitRadPoints > 0)
    {
      if(damRedButton->handle_events(player->damRedPoints)
	 && player->damRedPoints < 3 && player->useSkillPoint())
	{
	  player->damRedPoints++;
	  player->damRed += 10;
	}
    }
  else
    damRedButton->skillUnavail();
  
  shieldAmountButton->handle_tooltip();
  shieldRegenButton->handle_tooltip();
  shieldCapButton->handle_tooltip();

  armorAmountButton->handle_tooltip();
  hullAmountButton->handle_tooltip();

  evasionButton->handle_tooltip();
  hitRadButton->handle_tooltip();
  damRedButton->handle_tooltip();
}

void doAbilityTree(Player* player)
{
  apply_surface(0, 0, abilityTreeBG, screen);

  if(armorRepButton->handle_events(player->armorRepPoints) &&
     player->useSkillPoint())
    {
      player->armorRepPoints++;
      player->armorRepFact += 2;
    }

  if(player->level >= 3 && player->armorRepPoints > 0)
    {
      if(engShieldButton->handle_events(player->engShieldPoints) &&
	 player->engShieldPoints < 5 && player->useSkillPoint())
	{
	  player->engShieldPoints++;
	  player->ES_damRed += 10;
	}
    }
  else
    engShieldButton->skillUnavail();

  if(energy_amountButton->handle_events(player->energy_amountPoints) &&
     player->useSkillPoint())
    {
      player->energy_amountPoints++;
      player->energy += player->level * ENERGY_PER_POINT;
      player->maxEnergy += player->level * ENERGY_PER_POINT;
    }

  if(player->level >= 3 && player->energy_amountPoints > 0)
    {
      if(energy_regenButton->handle_events(player->energy_regenPoints) &&
	 player->useSkillPoint())
	{
	  player->energy_regenPoints++;
	  if(player->energy_regenPoints % 2 == 0)
	    player->energyRegen++;
	}
    }
  else
    energy_regenButton->skillUnavail();

  if(player->level >= 3 && player->energy_amountPoints > 0)
    {
      if(shieldRepButton->handle_events(player->shieldRepPoints) &&
	 player->useSkillPoint())
	{
	  player->shieldRepPoints++;
	  player->shieldRepFact++;
	}
    }
  else
    shieldRepButton->skillUnavail();

  if(player->level >= 5 && player->energy_regenPoints > 0)
    {
      if(novaRangeButton->handle_events(player->novaRangePoints) &&
	 player->useSkillPoint())
	{
	  player->novaRangePoints++;
	  player->novaRad += 30;
	}
    }
  else
    novaRangeButton->skillUnavail();

  if(player->level >= 5 && player->novaRangePoints > 0)
    {
      if(novaDamageButton->handle_events(player->novaDamagePoints) &&
	 player->useSkillPoint())
	{
	  player->novaDamagePoints++;
	  player->novaMult += .2;
	}
    }
  else
    novaDamageButton->skillUnavail();

  if(player->level >= 5 && player->energy_regenPoints > 0)
    {
      if(EB_costButton->handle_events(player->EB_costPoints) &&
	 player->EB_costPoints < 5 && player->useSkillPoint())
	{
	  player->EB_costPoints++;
	  player->EBcost--;
	}
    }
  else
    EB_costButton->skillUnavail();

  if(player->level >= 10 && player->EB_costPoints > 0)
    {
      if(EB_damageButton->handle_events(player->EB_damagePoints) &&
	 player->useSkillPoint())
	{
	  player->EB_damagePoints++;
	  player->EB_damage += 5;
	}
    }
  else
    EB_damageButton->skillUnavail();


  energy_amountButton->handle_tooltip();
  energy_regenButton->handle_tooltip();
  shieldRepButton->handle_tooltip();
  armorRepButton->handle_tooltip();
  engShieldButton->handle_tooltip();
  novaRangeButton->handle_tooltip();
  novaDamageButton->handle_tooltip();
  EB_costButton->handle_tooltip();
  EB_damageButton->handle_tooltip();
}
