void ledUpdate( void ) {
  
  targetPixel = targetPixel + (velocity / 30); 

  for( int i=0; i<NUM_LEDS; i++ ) {
    if( i == (int)targetPixel ) { leds[i] = CRGB::White; }
    else{ leds[i] = CRGB::Black; }
  }
  FastLED.show();
}

