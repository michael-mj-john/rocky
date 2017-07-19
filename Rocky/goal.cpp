#include "goal.h"

/* private */
/* public */
// To be called once per frame
void Goal::update() {
  if (framesRemaining == 0) {
    isDead = true;
    
    return;
  }

  // If time is running out (more than half of the frames have been spent, OR less than 2 second remaining), start flashing!
  if (framesRemaining / (float)initialFrames < 0.5 || framesRemaining < 60) {
    flashFrames++;

    if (flashFrames > 3) {
      flashFrames = 0;
      visible = !visible;
    }
  }
  
  framesRemaining--;
}

uint8_t Goal::getColor() {
  return visible ? onColor : offColor;
}


