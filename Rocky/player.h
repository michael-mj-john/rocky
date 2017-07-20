#ifndef player_h
#define player_h

#include "Arduino.h"

class Player {
  private:
  public:
    // The values of this players minimum and maximum flexes
    int minFlex = 0;
    int maxFlex = 0; //put back to -1 when maxvalue is established dynamically

    bool minConfigured = false;
    bool maxConfigured = false;
    
    float normalizedForce = 0;
    int dotPosition;
    int maxSamples;
    int maxSampleCount;
    
    // constructor
    Player( int dotPos ) : dotPosition( dotPos ) { }

    // Unset min and max Flex while simultaneously setting a new position
    void reset(int newPos);
  
    // Has this player had their min / max flex values configured?
    bool isInitialized();
  
    // Given a raw sensor reading (sensorValue), what is the actual "force" that this player is generating?
    // Normalized to [0 .. 1]
    void setNormalizedForce(int sensorValue);

};

#endif

