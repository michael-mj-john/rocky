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
  sensorValue = constrain(sensorValue, (float)minFlex, (float)maxFlex);
  //float realMin = max(0, minFlex);
  float range = maxFlex - minFlex;
  normalizedForce = constrain((sensorValue - minFlex) / range, 0.0, 1.0);
}

