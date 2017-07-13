void gameUpdate( void ) {

  float acceleration; 

  //accommodate "pendulum center"
  if( targetPixel < NUM_LEDS/2 ) {
    acceleration = gravity * -1;
  }
  else {
    acceleration = gravity;
  }

  velocity = velocity + (acceleration * 0.033); // assumes 30fps framerate
  float thrust = 4;

  if( greenPressed ) {
    velocity = velocity + (-1*(thrust * 0.033)); // will be negative
  }
  if( bluePressed ) {
    velocity = velocity + (thrust * 0.033); // will be negative
  }
  
  targetPixel = targetPixel + ( velocity / 30 );

  // test for going off either end, and reset if so
  if( (int)targetPixel >= NUM_LEDS-2 || targetPixel < 0 ) { 
   velocity = 0;
   gameState = start;
  }


  
}

