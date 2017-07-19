void ledUpdate() {

  float tailMax = 8;
  int midPixel = (int)targetPixel;

  //begin by blanking all LEDs
  fill_solid( leds, NUM_LEDS, CRGB::Black);

  //draw the "spaceship"
  leds[midPixel-1] = CHSV(HUE_BLUE, 255, 100);
  leds[midPixel] = CHSV(HUE_BLUE, 255, 255);
  leds[midPixel+1] = CHSV(HUE_BLUE, 255, 100);

  //if input is above threshold, draw scaled-length tail
  if( leftPlayer.normalizedForce > 0.05 ) {
    tail( -1, midPixel, leftPlayer.normalizedForce );
  } 
  if( rightPlayer.normalizedForce > 0.05 ) {
    tail( 1, midPixel, rightPlayer.normalizedForce );
  }

  //draw the "mouse" pixel
  goal.update();
  uint8_t goalColor = goal.getColor();
  leds[goal.position] = CRGB(goalColor, goalColor, goalColor);
  
  FastLED.show();
}

void tail (int multiplier, int center, float inputScale) {  //renders thrust tail
  static float tailMax = 12;
  float tailLength = tailMax * inputScale;
  int thisLength = (int)tailLength;
  int decrement = 255 / thisLength;

  // steady orange for adjacent pixel
  leds[center+(2*multiplier)] = CHSV(HUE_ORANGE, 255, 255);
  
  //increasing frequency and decreasing brightness for tail 
  for( int i=0; i<thisLength; i++ ) {
      int pixelIndex = center+(multiplier*(i+3));
      pixelIndex = max(pixelIndex, 0);
      pixelIndex = min(pixelIndex, NUM_LEDS-1);
      leds[pixelIndex] = CHSV(HUE_ORANGE, 255, 255-(decrement*i));
  }
}
