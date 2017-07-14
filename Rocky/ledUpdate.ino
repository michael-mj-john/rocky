void ledUpdate( double leftValue, double rightValue ) {

  double tailMax = 8;
  double tailLength = 0;
  int midPixel = (int)targetPixel;

  fill_solid( leds, NUM_LEDS, CRGB::Black);

  leds[midPixel-1] = CHSV(HUE_BLUE, 255, 100);
  leds[midPixel] = CHSV(HUE_BLUE, 255, 255);
  leds[midPixel+1] = CHSV(HUE_BLUE, 255, 100);

  if( leftValue > 0.05 ) {
    tailLength = (tailMax * leftValue); 
    tail( -1, midPixel, tailLength  );
  } 
  if( rightValue > 0.05 ) {
    tailLength = (tailMax * rightValue); 
    tail( 1, midPixel, tailLength );
  }

  leds[goalPixel] = CHSV(HUE_GREEN, 255, 100);
  
  FastLED.show();
}

void tail( int multiplier, int center, double tailLength ) {

  int thisLength = (int)tailLength;

  // steady orange for adjacent pixel
  leds[center+(2*multiplier)] = CHSV(HUE_ORANGE, 255, 255);
  
  //increasing frequency and decreasing brightness for tail 
  for( int i=0; i<thisLength; i++ ) {
//    if( frameCount % (5-i) == 0 ) {
      leds[center+(multiplier*(i+3))] = CHSV(HUE_ORANGE, 255, 255-(40*i));
//    }
  }
}
