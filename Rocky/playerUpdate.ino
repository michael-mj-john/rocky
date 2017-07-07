void gameUpdate( void ) {

  velocity = velocity + acceleration;
 // This is a turd
  if( targetPixel > NUM_LEDS / 2 ) { 
    acceleration = acceleration - seconds^2;
  }
  else {
    acceleration = acceleration + seconds^2;
  }
  
}

