#include "player.h"

/* private */
/* public */

// Unset min and max Flex while simultaneously setting a new position
void Player::reset(int newPos) {
  minFlex = 0;
  maxFlex = 0;

  minConfigured = false;
  maxConfigured = false;

  dotPosition = newPos;
}

// Has this player had their min / max flex values configured?
bool Player::isInitialized() {
  return minConfigured && maxConfigured;
}

// Given a raw sensor reading (sensorValue), what is the actual "force" that this player is generating?
// Normalized to [0 .. 1]
void Player::setNormalizedForce(int sensorValue) {
  float sensorFloat = (float)sensorValue;
  sensorFloat = constrain(sensorFloat, (float)minFlex, (float)maxFlex);
  float range = maxFlex - minFlex;
  normalizedForce = constrain((sensorFloat - minFlex) / range, 0.0, 1.0);
}

