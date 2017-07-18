#include "player.h"

/* private */
/* public */
// Has this player had their min / max flex values configured?
bool Player::isInitialized() {
  return minFlex >= 0 && maxFlex >= 0;
}

// Given a raw sensor reading (sensorValue), what is the actual "force" that this player is generating?
// Normalized to [0 .. 1]
float Player::getNormalizedForce(int sensorValue) {
  float range = maxFlex - minFlex;
  return (sensorValue - minFlex) / range;
}

