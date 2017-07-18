void gameUpdate( void ) {
  double leftValue = analogRead(LEFT_PLAYER_PIN);
  leftValue = leftPlayer.getNormalizedForce(leftValue);
  velocity = velocity + ((thrustMax * leftValue) * .033);
  
  double rightValue = analogRead(RIGHT_PLAYER_PIN);
  rightValue = rightPlayer.getNormalizedForce(rightValue);
  velocity = velocity - ((thrustMax * rightValue) * .033);

  targetPixel = targetPixel + ( velocity / 30 );

  // test for going off either end, and reset if so
  if( (int)targetPixel >= NUM_LEDS-2 || targetPixel < 0 ) { 
   velocity = 0;
   gameState = prep;
  }

  if( (int)targetPixel > goalPixel-1 && (int)targetPixel < goalPixel+1 ) {
    framesAtTarget++;
    if( framesAtTarget > TARGET_FRAMES ) {
      gameState = win;
      framesAtTarget = 0;
    } 
  }
  else {
    framesAtTarget = 0;
  }

  ledUpdate( leftValue, rightValue );
}

