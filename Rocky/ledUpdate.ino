void ledUpdate( void ) {

  int tailLength = 8;
  int midPixel = (int)targetPixel;

  fill_solid( leds, NUM_LEDS, CRGB::Black);

  leds[midPixel-1] = CHSV(HUE_BLUE, 255, 100);
  leds[midPixel] = CHSV(HUE_BLUE, 255, 255);
  leds[midPixel+1] = CHSV(HUE_BLUE, 255, 100);

  if( greenPressed ) {
    tail( 1, midPixel );
  }
  if( bluePressed ) {
    tail( -1, midPixel );
  }
  
  FastLED.show();
}

void tail( int multiplier, int center ) {

    int midPixel = center;
    
    leds[midPixel+(2*multiplier)] = CHSV(HUE_ORANGE, 255, 100);
    if( frameCount % 5 == 0 ) {
      leds[midPixel+(3*multiplier)] = CHSV(HUE_ORANGE, 255, 100);
    }
    if( frameCount % 3 == 0 ) {
      leds[midPixel+(4*multiplier)] = CHSV(HUE_RED, 255, 50);
    }
 }


