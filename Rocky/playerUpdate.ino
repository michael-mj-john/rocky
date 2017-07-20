// Flashes the number of points the player has in the middle of the LEDs.
// Not async, will block.
void showPoints(char hue) {
   fill_solid( leds, NUM_LEDS, CRGB::Black);
  
  int startPos = (NUM_LEDS / 2) - points;
  
  for (int j = 0; j < 5; j++) {
    // Draw points separated by 1 pixel each
    for (int i = startPos; i < startPos + (points * 2); i+=2) {
      leds[i] = CHSV(HUE_RED, 255, 100);
    }
    FastLED.show();
    delay(300);
  }
}

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
  if( (int)targetPixel >= goal.pos-1 && (int)targetPixel <= goal.pos+1 ) {
    framesAtTarget++;
    if( framesAtTarget > TARGET_FRAMES + (points * 2) ) {
      gameState = win;
      framesAtTarget = 0;
    } 
  }
  else {
    framesAtTarget = 0;
  }

  goal.update();

  // GAME OVER
  if (goal.isDead) {
    showPoints(HUE_RED);

    // Reset game
    points = 0;
    gameState = start;
  }
  
  ledUpdate();
}

