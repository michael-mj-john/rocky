void gameUpdate( void ) {

  float acceleration; 

  double leftValue = analogRead(A1);
  leftValue = leftValue / 1024;
  velocity = velocity + ((thrustMax * leftValue) * .033);
  double rightValue = analogRead(A0);
  rightValue = rightValue / 1024;
  velocity = velocity - ((thrustMax * rightValue) * .033);

  targetPixel = targetPixel + ( velocity / 30 );

  // test for going off either end, and reset if so
  if( (int)targetPixel >= NUM_LEDS-2 || targetPixel < 0 ) { 
   velocity = 0;
   gameState = start;
  }

  if( (int)targetPixel > goalPixel-1 && (int)targetPixel < goalPixel+1 ) {
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

