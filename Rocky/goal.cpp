#include "goal.h"

/* private */
/* public */
// To be called once per frame
void Goal::update() {
  if (lifeRemaining == 0) {
    return;
  }

  // If time is running out (more than half of the frames have been spent, OR less than 2 second remaining), start flashing!
  if (lifeRemaining / (float)initialLife < 0.5 || lifeRemaining < 60) {
    flashFrames++;
    if( lifeRemaining > 30 ) {
      if (flashFrames > 3) {
        flashFrames = 0;
        visible = !visible;
      }
    }
    else {
        if (flashFrames > 1) {
        flashFrames = 0;
        visible = !visible;
      }
    }

  }
  
  lifeRemaining--;
}

// Resets position and lifetime based on the value of points and GOAL_TIME
void Goal::reset(int numLEDS, int points, int goalTime) {
  int maxSpawnDistance = min(numLEDS/2-1, 10 + (points*5));

  if (rand() % 2 == 0) {
    pos = numLEDS/2 + 5 + random(0, 100)/100.0 * maxSpawnDistance;
  } else {
    pos = numLEDS/2 - 5 - random(0, 100)/100.0 * maxSpawnDistance;
  }

  lifeRemaining = initialLife = goalTime;
  visible = true;
}

bool Goal::isDead() {
  return lifeRemaining <= 0;
}

uint8_t Goal::getColor() {
  return visible ? onColor : offColor;
}


