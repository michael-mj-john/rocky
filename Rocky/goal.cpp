#include "goal.h"

/* private */
/* public */
// To be called once per frame
void Goal::update() {
  if (lifeRemaining == 0) {
    isDead = true;
    return;
  }

  // If time is running out (more than half of the frames have been spent, OR less than 2 second remaining), start flashing!
  if (lifeRemaining / (float)initialLife < 0.5 || lifeRemaining < 60) {
    flashFrames++;

    if (flashFrames > 3) {
      flashFrames = 0;
      visible = !visible;
    }
  }
  
  lifeRemaining--;
}

void Goal::reset(int newPos, int newLifetime) {
  position = newPos;

  lifeRemaining = initialLife = newLifetime;
}

uint8_t Goal::getColor() {
  return visible ? onColor : offColor;
}


