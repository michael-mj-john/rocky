void gameUpdate( void ) {
  float leftValue = analogRead(LEFT_PLAYER_PIN);
  leftPlayer.setNormalizedForce(leftValue);
  velocity = velocity + ((thrustMax * leftPlayer.normalizedForce) * .033);
  
  float rightValue = analogRead(RIGHT_PLAYER_PIN);
  rightPlayer.setNormalizedForce(rightValue);
  velocity = velocity - ((thrustMax * rightPlayer.normalizedForce) * .033);

  targetPixel = targetPixel + ( velocity / 30 );

  // test for going off either end, and reset if so
  if( (int)targetPixel >= NUM_LEDS-2 || targetPixel <= 0 ) { 
   velocity = 0;
   gameState = start;
  }

  // test for successful 'catch'
  if( (int)targetPixel >= goal.position-1 && (int)targetPixel <= goal.position+1 ) {
    framesAtTarget++;
    if( framesAtTarget > TARGET_FRAMES + (points * 2) ) {
      gameState = win;
      framesAtTarget = 0;
    } 
  }
  else {
    framesAtTarget = 0;
  }

  if (goal.isDead) {
    points = 0;
    
    for (int j = 0; j < 5; j++) {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV(HUE_RED, 255, 100);
      }
      FastLED.show();
      delay(300);
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB(0,0,0);
      }
      FastLED.show(0);
      delay(300);
    }

    gameState = start;
  }

  ledUpdate();
}

