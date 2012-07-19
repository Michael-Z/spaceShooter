//classes.h

#ifndef CLASSES_H
#define CLASSES_H

#include "SDL/SDL.h"

#include <list>

//clickable button
class Button
{
 private:
  SDL_Surface *buttonSheet;
  SDL_Rect box;
  SDL_Rect* clip;
  SDL_Rect* mainClip; //regular clip
  SDL_Rect* overClip; // clip for mouse over
  SDL_Rect* clicked;  //when button is clicked

 public:
  Button(int x, int y, int w, int h, SDL_Surface* theButtonSheet,
	 SDL_Rect* buttonClip,
	 SDL_Rect* mouseOverClip,
	 SDL_Rect* buttonClicked);
  
  bool inButton(int tX, int tY);
  bool handle_events();
  void show();
};

//basic projectile type, others inherit from
class Projectile
{
 protected:
  bool homing;
  int x, y;

  int xVel, yVel;

  SDL_Surface* picture;

  //int velocity;
  int radius;
  int range;
  int damage;

  int dist;

 public:
  Projectile(SDL_Surface *image, int startx, int starty, int sXvel, int sYvel,
	     int dam, int rad, int ran, bool homing);
  ~Projectile();

  bool isHoming() { return homing; }

  void doHoming(int tX, int tY);
  void move();
  bool isOutBounds();
  void show();
  bool collide(int cX, int cY, int rad);
  int getDist();
  int getRange();
  int getDamage();
  int getRad();
  int getX();
  int getY();
};

//Basic ship class, enemies, player based off of
class Ship
{
 protected:
  bool isPlayer;

  int score; //score from killing enemies

  //target for enemies
  Ship *target;

  //The X and Y offsets of the ship
  int x, y;

  //unit vector of facing direction
  double x1, y1;
    
  //The velocity of the ship
  int xVel, yVel;

  int radius;
  
  int maxSpeed;

  //surface of the ship
  SDL_Surface *ship;

  //metal slugs container
  std::list<Projectile*> slugs;
    
 public:
  ~Ship();

  //defences
  int evasion;
  int hitRadius;
  int damRed;

  int maxHull;
  int hull;

  int maxArmor;
  int armor;

  int maxShield;
  int shield;
  int shieldRegen; //% per 10 frames
  bool shieldCap; // regeneration increases while less

  //weapon properties
  int MS_speed;
  int MS_damage;
  int MS_radius;
  int MS_range;
  int MS_rate;

  int MG_speed;
  int MG_damage;
  int MG_radius;
  int MG_range;
  int MG_rate;
  bool MG_double;

  int SG_speed;
  int SG_damage;
  int SG_radius;
  int SG_range;
  int SG_rate;
  bool SG_double;

  //homing missile properties
  int homing_speed;
  int homing_damage;
  int homing_radius;
  int homing_range;
  int homing_rate;
  bool HM_double;

  //do what the ship is supposed to do
  void doUnit();

  //Moves the ship, 
  void move();
  void regenShield();


  //undos an invalid move
  void unMove();
  
  //face direction of coords
  void faceDirection(int x, int y);

  //show ship
  void show();

  //take damage
  void takeDamage(int damage, bool collide = false);

  //shoot various projectiles
  void shootProjectile(SDL_Surface* image, int speed, int range, int damage,
		       int radius, bool isHoming = false);

  void shootShotgun();
  void shootHoming();
  void shootMGdouble();

  //move various projectiles
  std::list<Projectile*> moveProjectiles(std::list<Projectile*> bullets);

  //die with explosion!
  void die();

  int getRad();
  int getX();
  int getY();
  int getXvel();
  int getYvel();
  double getxDir();
  double getyDir();

  int getMaxShield() { return maxShield; }
  int getMaxArmor() { return maxArmor; }
  int getMaxHull() { return maxHull; }

  int getShield() { return shield; }
  int getArmor() { return armor; }
  int getHull() { return hull;}

};

class Player : public Ship
{
 private:
  //if the keys are pressed
  bool up;
  bool down;
  bool left;
  bool right;

  //mouse buttons
  bool lmouse;
  bool rmouse;

  int lStart; //when mouse button is clicked
  int rStart;
  
  //current angle
  double angle;

  //current lclick weapon 1-5?
  int weapon;
  int ability;

 public:
  Player();

  int level;
  Uint32 exp;
  Uint32 oldExp;
  Uint32 levelExp;

  int skillPoints;

  //skill points
  int MS_damagePoints;
  int MS_rangePoints;
  int MS_radiusPoints;
  int MS_ratePoints;

  int MG_damagePoints;
  int MG_speedPoints;
  int MG_rangePoints;
  int MG_doublePoints;

  int SG_rangePoints;
  int SG_damagePoints;
  int SG_ratePoints;
  int SG_doublePoints;

  int HM_rangePoints;
  int HM_damagePoints;
  int HM_radiusPoints;
  int HM_doublePoints;

  
  int shieldAmountPoints;
  int shieldRegenPoints;
  int shieldCapPoints;
  int armorAmountPoints;
  int hullAmountPoints;
  int evasionPoints;
  int hitRadPoints;
  int damRedPoints;

  int energy_amountPoints;
  int energy_regenPoints;
  int shieldRepPoints;
  int armorRepPoints;
  int engShieldPoints;
  int novaRangePoints;
  int novaDamagePoints;
  int EB_costPoints;
  int EB_damagePoints;

  void regenEnergy();

  void doUnit();

  //Takes key presses and adjusts the ship's velocity
  void handle_input();

  //face mouse
  void faceMouse();

  //accelerate
  void accelerate();

  //do left click action
  void doLeftClick();
  void doRightClick();

  //center Camera
  void set_camera();

  //energy
  int maxEnergy;
  int energy;
  int energyRegen; //energy regen per 10 frames

  //skill attrubtes
  int shieldRepFact;
  int armorRepFact;

  //energy nova
  double novaMult; //damage = novaPoints * novaMult
  int novaRad; //radius of the nova
  int novaPoints; //energy points used for charging nova
  int novaStage; //current stage of nova

  //energyBolt
  int EB_speed;
  int EB_damage;
  int EB_radius;
  int EB_range;
  int EB_rate;
  int EB_timer;
  int EBcost;

  //energy shield
  int ES_startDamRed;
  int ES_damRed;
  bool ES_on;

  int getLevel() { return level; }

  int getMaxEnergy() { return maxEnergy; }
  int getEnergy();

  int getSkillPoints() { return skillPoints; }
  bool useSkillPoint();

  void updateStatusBars();

  void doLevel();

  void repairShield();
  void repairArmor();

  void chargeNova();
  void doNova();
};

//basic enemy, dumb and shoots molten slugs
class Grunt : public Ship
{
 public:
  Grunt(int startx, int starty, Ship *target);
  void doUnit(std::list<Grunt*>::iterator it);

  void accelerate();
};

class Boomer : public Ship
{
 private:
  int damage;

 public:
  Boomer(int startx, int starty, Ship* player,
	 int startxVel = 0, int startyVel = 0);
  void accelerate();
  void doUnit();
  void die();
};

class Stealth : public Ship
{
 public:
  Stealth(int startx, int starty, Ship *target);
  void doUnit(std::list<Stealth*>::iterator it);

  void accelerate();
};

class Carrier : public Ship
{
 public:
  Carrier(int startx, int starty, Ship *target);
  void doUnit(std::list<Carrier*>::iterator it);

  using Ship::die;
  void die();
  void accelerate();
};

//The timer
class Timer
{
 private:
  //The clock time when the timer started
  int startTicks;
    
  //The ticks stored when the timer was paused
  int pausedTicks;
    
  //The timer status
  bool paused;
  bool started;
    
 public:
  //Initializes variables
  Timer();
    
  //The various clock actions
  void start();
  void stop();
  void pause();
  void unpause();
    
  //Gets the timer's time
  int get_ticks();
    
  //Checks the status of the timer
  bool is_started();
  bool is_paused();    
};


class Explosion
{
 private:
  int x;
  int y;

  int stage;

 public:
  Explosion(int sX, int sY);
  int get_stage();
  void show();


};

class Tooltip
{
 private:
  int x;
  int y;
  int w;
  int h;

  SDL_Surface* image;

 public:
  Tooltip(int sX, int sY, int sW, int sH, SDL_Surface *ttImage);

  bool inTooltip(int tX, int tY);
  void handle_events();
};

class SkillButton
{
 public:
  SkillButton(int sx, int sy, int sw, int sh, SDL_Surface *ttImage);
  ~SkillButton();


  int x;
  int y;
  int w;
  int h;

  Button* button;
  Tooltip* tooltip;

  bool handle_events(int points);

  void handle_tooltip();
  void skillUnavail();
  
};

#endif
