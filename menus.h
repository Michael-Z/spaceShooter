//menus.h

#ifndef MENUS_H
#define MENUS_H

bool handle_menu_input();
bool doMainMenu();
void instructionsMenu();
void gameOverMenu();
void doPauseMenu();
void doSkillMenu(Player *player);
void doOffensiveTree(Player *player);
void doDefensiveTree(Player *player);
void doAbilityTree(Player *player);

#endif
