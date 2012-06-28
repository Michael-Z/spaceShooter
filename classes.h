//classes.h

#ifndef CLASSES_H
#define CLASSES_H

#include <list>

//basic projectile type, others inherit from
class Projectile
{
 protected:
  int x, y;

  int xVel, yVel;

  SDL_Surface* picture;

  int velocity;
  int radius;
  int range;
  int damage;

  int dist;

 public:
  Projectile(SDL_Surface *image, int startx, int starty, double xDir,
	     double yDir, int dam, int vel, int rad, int ran);

  void move();
  bool isOutBounds();
  void show();
  bool collide(int cX, int cY, int rad);
  int getDist();
  int getRange();
};

//Basic ship class, enemies, player based off of
class Ship
{
 protected:
  //The X and Y offsets of the ship
  int x, y;

  //unit vector of facing direction
  double x1, y1;
    
  //The velocity of the ship
  int xVel, yVel;

  int radius;

  //surface of the ship
  SDL_Surface *ship;

  //defences
  int maxHull;
  int hull;

  int maxArmor;
  int armor;

  int maxShield;
  int shield;

  //weapon properties
  int MS_speed;
  int MS_damage;
  int MS_radius;
  int MS_range;
  int MS_rate;

  //metal slugs container
  std::list<Projectile*> slugs;
    
 public:
  //do what the ship is supposed to do
  void doUnit();

  //Moves the shipt
  void move();
  
  //face direction of coords
  void faceDirection(int x, int y);

  //show ship
  void show();

  //take damage
  void takeDamage(int damage);

  //shoot various projectiles
  void shootMoltenSlug();

  //move various projectiles
  void moveProjectiles(std::list<Projectile*> bullets);

  int getShield();
  int getArmor();
  int getHull();

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

  //current angle
  double angle;

  //energy
  int maxEnergy;
  int energy;

  //current lclick weapon 1-5?
  int weapon;

 public:
  Player();

  void doUnit();

  //Takes key presses and adjusts the ship's velocity
  void handle_input();

  //face mouse
  void faceMouse();

  //accelerate
  void accelerate();

  //do left click action
  void doLeftClick();

  //center Camera
  void set_camera();

  //void show();

  int getEnergy();

  void updateStatusBars();
};

//basic enemy, dumb and shoots molten slugs
class Grunt : public Ship
{
 private:
  Player *target;

 public:
  Grunt(int startx, int starty, Player *target);
  void doUnit(std::list<Grunt*> grunts, std::list<Grunt*>::iterator it);

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



#endif
