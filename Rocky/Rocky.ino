#include "FastLED.h"
#include "player.h"

#define NUM_LEDS 144
#define DATA_PIN 7
#define LEFT_PLAYER_PIN A0
#define RIGHT_PLAYER_PIN A1
#define TARGET_FRAMES 10

CRGB leds[NUM_LEDS];

float targetPixel;
long lastDrawMillis;
int frameCount;
int points=0;

enum gameStates { prep, start, play, win };
gameStates gameState = start;
bool calibrateMode = 1;

float velocity;
static float thrustMax = 4;

uint16_t framesAtTarget;
int goalPixel;

Player leftPlayer(NUM_LEDS/2 - 1);
Player rightPlayer(NUM_LEDS/2 + 1);

int leftSensorRead;
int rightSensorRead;

void setup() {
  Serial.begin(9600);
  pinMode(3,INPUT); // left button 
  pinMode(4, INPUT); // right button
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  randomSeed(analogRead(A5));
  frameCount = 0;
}

void loop() {
  // if reset button is pressed
  if (digitalRead(2) == HIGH) {
    gameState = start;
  }
  
  switch (gameState) {

    case start:
      gameStart();
      break;
      
    case win:
      pointScored();
      break;
      
    case play:
      if (millis() > lastDrawMillis + 1000/30) { // 30 fps LED update
        frameCount < 30 ? frameCount++ : frameCount = 0;
        if( calibrateMode ) {
          preGame();
        }
        else {
          gameUpdate();
        }
        lastDrawMillis = millis();
      }
      break;
      
    default:
      break;
  }
}


void preGame( void ) {
  static int minRead = 200;
  static int maxRead = 350;
  
  // read sensor input
  leftSensorRead = analogRead(LEFT_PLAYER_PIN);
  rightSensorRead = analogRead(RIGHT_PLAYER_PIN);

  Serial.print("left: ");
  Serial.println(leftSensorRead);
  Serial.print("right: ");
  Serial.println(rightSensorRead);

  // Serial.println(leftPlayer.dotPosition);
  // Serial.println(rightPlayer.dotPosition);

  // If either the left or right player has not had their minFlex configured
  if (leftPlayer.minFlex < 0 || rightPlayer.minFlex < 0) {
    if (/*leftSensorRead < minRead && */leftPlayer.minFlex < 0) {
      leds[leftPlayer.dotPosition] = CRGB(0,0,0);
      leftPlayer.dotPosition--;
      leds[leftPlayer.dotPosition] = CHSV(HUE_BLUE, 255, 100);
      
      if (leftPlayer.dotPosition == 0) {
        leftPlayer.minFlex = leftSensorRead;
      }
    }
    
    if (/*rightSensorRead < minRead && */rightPlayer.minFlex < 0) {
      leds[rightPlayer.dotPosition] = CRGB(0,0,0);
      rightPlayer.dotPosition++;
      leds[rightPlayer.dotPosition] = CHSV(HUE_BLUE, 255, 100);
      
      if (rightPlayer.dotPosition == NUM_LEDS - 1) {
        rightPlayer.minFlex = rightSensorRead;
      }
    }
  } else { // else we should configure maxFlex
    if (leftSensorRead > maxRead && leftPlayer.maxFlex < 0) {
      leds[leftPlayer.dotPosition] = CRGB(0,0,0);
      leftPlayer.dotPosition++;
      leds[leftPlayer.dotPosition] = CHSV(HUE_BLUE, 255, 100);
      
      if (leftPlayer.dotPosition == NUM_LEDS / 2) {
        leftPlayer.maxFlex = leftSensorRead;
      }
    }
    
    if (rightSensorRead > maxRead && rightPlayer.maxFlex < 0) {
      leds[rightPlayer.dotPosition] = CRGB(0,0,0);
      rightPlayer.dotPosition--;
      leds[rightPlayer.dotPosition] = CHSV(HUE_BLUE, 255, 100);
      
      if (rightPlayer.dotPosition == NUM_LEDS / 2) {
        rightPlayer.maxFlex = rightSensorRead;
      }
    }
  }

  FastLED.show();
      
  /*// When someone presses the start button, it's time to go
  leftPlayer.minFlex = leftSensorRead;
  rightPlayer.minFlex = rightSensorRead;

  if( leftPlayer.dotPosition == targetPixel - 1 && rightPlayer.dotPosition == targetPixel + 1 ) {
    // calibrateMode = 0;
  } */
  if (leftPlayer.isInitialized() && rightPlayer.isInitialized()) {
    calibrateMode = 0;
    //Serial.println("BUTTS");
  }
}

void gameStart(void) {
  targetPixel = NUM_LEDS/2;
  velocity = 0;
  goalPixel = random(6,NUM_LEDS-6);
  gameState = play;
  calibrateMode = 1;
  leftPlayer.reset(NUM_LEDS/2 - 1);
  rightPlayer.reset(NUM_LEDS/2 + 1);
  
  // Draw the center point
  leds[(int)targetPixel] = CHSV(HUE_BLUE, 255, 255);
  FastLED.show();

  Serial.println("game reset");
}

void pointScored( void ) {

  points++;
  for( int j=0; j<points; j++ ) {
    for( int i =0; i<NUM_LEDS; i++ ) {
      leds[i] = CHSV(HUE_GREEN, 255, 100);
    }
    FastLED.show();
    delay(300);
    for( int i =0; i<NUM_LEDS; i++ ) {
      leds[i] = CRGB(0,0,0);
    }
    FastLED.show(0);
    delay(300);
  }
  
  gameState = start;
  
}

