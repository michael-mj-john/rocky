#ifndef player_h
#define player_h

#include "Arduino.h"

class Player {
private:
public:
  // The values of this players minimum and maximum flexes
  int minFlex = -1;
  int maxFlex = -1;

  // Has this player had their min / max flex values configured?
  bool isInitialized();

  // Given a raw sensor reading (sensorValue), what is the actual "force" that this player is generating?
  // Normalized to [0 .. 1]
  float getNormalizedForce(int sensorValue);
};

#endif

