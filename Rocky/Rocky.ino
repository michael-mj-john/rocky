#include "FastLED.h"
#include "player.h"
#include "goal.h"

#define NUM_LEDS 144
#define DATA_PIN 7
#define LEFT_PLAYER_PIN A0
#define RIGHT_PLAYER_PIN A1
#define TARGET_FRAMES 5
#define GOAL_TIME 400

CRGB leds[NUM_LEDS];

double targetPixel;
long lastDrawMillis;
int frameCount;
int points=0;

enum gameStates { prep, start, play, win };
gameStates gameState = start;
bool calibrateMode = 1;

double velocity;
static double thrustMax = 4;

uint16_t framesAtTarget;
//int goalPixel;
Goal goal(random(6,NUM_LEDS-6), GOAL_TIME);

Player leftPlayer(NUM_LEDS/2 - 1);
Player rightPlayer(NUM_LEDS/2 + 1);

int leftSensorRead;
int rightSensorRead;

void setup() {
  Serial.begin(9600);
  pinMode(3,INPUT); // left button 
  pinMode(4, INPUT); // right button
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  randomSeed(analogRead(A0));
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
  int minRead = 200;
  int maxRead = 350;
  
  // read sensor input
  leftSensorRead = analogRead(LEFT_PLAYER_PIN);
  rightSensorRead = analogRead(RIGHT_PLAYER_PIN);

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
      if( leftPlayer.dotPosition > ( NUM_LEDS / 2 - 10 )) {
        leftPlayer.maxSamples += leftSensorRead;
        leftPlayer.maxSampleCount++;
      }
      if (leftPlayer.dotPosition >= NUM_LEDS / 2) {
        leftPlayer.maxFlex = leftPlayer.maxSamples / leftPlayer.maxSampleCount;
      }
    }
    
    if (rightSensorRead > maxRead && rightPlayer.maxFlex < 0) {
      leds[rightPlayer.dotPosition] = CRGB(0,0,0);
      rightPlayer.dotPosition--;
      leds[rightPlayer.dotPosition] = CHSV(HUE_BLUE, 255, 100);
      if( rightPlayer.dotPosition < ( NUM_LEDS / 2 + 10 )) {
        rightPlayer.maxSamples += rightSensorRead;
        rightPlayer.maxSampleCount++;
      }
      if (rightPlayer.dotPosition <= NUM_LEDS / 2) {
        rightPlayer.maxFlex = rightPlayer.maxSamples / rightPlayer.maxSampleCount;
      }
     }
  }

  FastLED.show();
      
  if (leftPlayer.isInitialized() && rightPlayer.isInitialized()) {
    calibrateMode = 0;
  }
}

void gameStart(void) {
  velocity = 0;
  gameState = play;
  calibrateMode = 1;
  leftPlayer.reset(NUM_LEDS/2 - 1);
  rightPlayer.reset(NUM_LEDS/2 + 1);

  // Configure goal (but don't show it yet!)
  goal.reset(random(6,NUM_LEDS-6), GOAL_TIME);

  // Draw target
  targetPixel = NUM_LEDS/2;
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
    
    clearDisplay();
    delay(300);
  }
  
  gameState = start;
  
}

// Turn off all LEDS
void clearDisplay() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0,0,0);
  }
  FastLED.show(0);
}

