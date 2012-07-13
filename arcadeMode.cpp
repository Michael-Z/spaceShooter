//arcadeMode.cpp
//governs rules for arcade mode.

#include "globals.h"

//temporary arcade mode
void doArcadeMode(Player* player0)
{
  if(frame % 300 == 0)
    grunts.push_back(new Grunt(500, 500, player0));

  if(frame % 80 == 0)
    boomers.push_back(new Boomer(500, 1000, player0));

  if(frame % 500 == 0)
    stealths.push_back(new Stealth(1000, 1000, player0));

  if(frame % 800 == 0)
    carriers.push_back(new Carrier(1500, 1500, player0));

}
