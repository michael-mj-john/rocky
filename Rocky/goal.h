#ifndef goal_h
#define goal_h

#include "Arduino.h"

class Goal {
  private:
  public:
  int position;
  int framesOver = 0;

  // constructor
  Goal(int newPos) : position(newPos) { }
};

#endif

