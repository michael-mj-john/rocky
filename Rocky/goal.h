#ifndef goal_h
#define goal_h

#include "Arduino.h"

class Goal {
  private:
  public:
  int position;
  int framesOver = 0;
  int initialFrames, framesRemaining = 200; // How long will this goal exist, measured in frames
  int flashFrames = 0;
  bool visible = true;
  bool isDead = false;
  uint8_t onColor = 80;
  uint8_t offColor = 0;

  // constructor
  Goal(int newPos) : position(newPos) { }

  void update();
  uint8_t getColor();
};

#endif

