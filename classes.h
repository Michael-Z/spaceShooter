//classes.h

#ifndef CLASSES_H
#define CLASSES_H

#include "SDL/SDL.h"

#include <list>

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

  //defences
  int maxHull;
  int hull;

  int maxArmor;
  int armor;

  int maxShield;
  int shield;
  int shieldRegen; //% per 10 frames

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

  int SG_speed;
  int SG_damage;
  int SG_radius;
  int SG_range;
  int SG_rate;

  //homing missile properties
  int homing_speed;
  int homing_damage;
  int homing_radius;
  int homing_range;
  int homing_rate;

  //metal slugs container
  std::list<Projectile*> slugs;
    
 public:
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
  void takeDamage(int damage);

  //shoot various projectiles
  void shootProjectile(SDL_Surface* image, int speed, int range, int damage,
		       int radius, bool isHoming = false);

  void shootShotgun();
  void shootHoming();

  //move various projectiles
  std::list<Projectile*> moveProjectiles(std::list<Projectile*> bullets);

  //die with explosion!
  void die();

  int getShield();
  int getArmor();
  int getHull();

  int getRad();
  int getX();
  int getY();
  int getXvel();
  int getYvel();
  double getxDir();
  double getyDir();
};

class Player : public Ship
{
 private:
  Uint32 exp;

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

  //energy
  int maxEnergy;
  int energy;
  int energyRegen; //energy regen per 10 frames

  //current lclick weapon 1-5?
  int weapon;
  int ability;

  int shieldRepFact;

 public:
  Player();

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

  //void show();

  int getEnergy();

  void updateStatusBars();
};

//basic enemy, dumb and shoots molten slugs
class Grunt : public Ship
{
 public:
  Grunt(int startx, int starty, Player *target);
  ~Grunt();
  void doUnit(std::list<Grunt*>::iterator it);

  void accelerate();
};

class Boomer : public Ship
{
 private:
  int damage;

 public:
  Boomer(int startx, int starty, Player* player);
  void accelerate();
  void doUnit();
  void die();
};

class Stealth : public Ship
{
 public:
  Stealth(int startx, int starty, Player *target);
  void doUnit(std::list<Stealth*>::iterator it);

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


#endif
