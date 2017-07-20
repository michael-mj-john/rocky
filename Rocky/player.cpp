#include "player.h"

/* private */
/* public */

// Unset min and max Flex while simultaneously setting a new position
void Player::reset(int newPos) {
  minFlex = -1;
  maxFlex = -1;

  dotPosition = newPos;
}

// Has this player had their min / max flex values configured?
bool Player::isInitialized() {
  return minFlex >= 0 && maxFlex >= 0;
}

// Given a raw sensor reading (sensorValue), what is the actual "force" that this player is generating?
// Normalized to [0 .. 1]
void Player::setNormalizedForce(int sensorValue) {
  sensorValue = min( sensorValue, maxFlex );
  float range = maxFlex - minFlex;
  normalizedForce = max(0, min((sensorValue - minFlex) / range, 1));
}

