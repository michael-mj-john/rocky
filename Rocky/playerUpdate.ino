void gameUpdate( void ) {

  float acceleration; 

  //accommodate "pendulum center"
/*  if( targetPixel < NUM_LEDS/2 ) {
    acceleration = gravity * -1;
  }
  else {
    acceleration = gravity;
  }

  velocity = velocity + (acceleration * 0.033); // assumes 30fps framerate
*/
  double leftValue = analogRead(A4);
  leftValue = leftValue / 1024;
  velocity = velocity + ((thrustMax * leftValue) * .033);
  double rightValue = analogRead(A3);
  rightValue = rightValue / 1024;
  velocity = velocity - ((thrustMax * rightValue) * .033);

  targetPixel = targetPixel + ( velocity / 30 );

  // test for going off either end, and reset if so
  if( (int)targetPixel >= NUM_LEDS-2 || targetPixel < 0 ) { 
   velocity = 0;
   gameState = start;
  }

  if( (int)targetPixel == goalPixel ) {
    framesAtTarget++;
    if( framesAtTarget > 10 ) {
      gameState = win;
      framesAtTarget = 0;
    } 
  }
  else {
    framesAtTarget = 0;
  }
  

  ledUpdate( leftValue, rightValue );

  
}

