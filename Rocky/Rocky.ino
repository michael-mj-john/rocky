#include "FastLED.h"
#include "player.h"

#define NUM_LEDS 144
#define DATA_PIN 7
#define LEFT_PLAYER_PIN A0
#define RIGHT_PLAYER_PIN A1
#define TARGET_FRAMES 10

CRGB leds[NUM_LEDS];

double targetPixel;
long lastDrawMillis;
int frameCount;

enum gameStates { prep, start, play, win };
gameStates gameState = start;
bool calibrateMode = 1;

double velocity;
static double thrustMax = 4;

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
          
     // read sensor input
      leftSensorRead = analogRead(LEFT_PLAYER_PIN);
      rightSensorRead = analogRead(RIGHT_PLAYER_PIN);

    Serial.println(leftPlayer.dotPosition);
    Serial.println(rightPlayer.dotPosition);

      if( leftSensorRead < 100 ) {
        leds[leftPlayer.dotPosition] = CRGB(0,0,0);
        leftPlayer.dotPosition--;
        leds[leftPlayer.dotPosition] = CHSV(HUE_BLUE, 255, 100);
        if( leftPlayer.dotPosition == 0 ) {
          leftPlayer.minFlex = leftSensorRead;
        }
      }
      if( rightSensorRead < 100 ) {
       leds[rightPlayer.dotPosition] = CRGB(0,0,0);
       rightPlayer.dotPosition++;
       leds[rightPlayer.dotPosition] = CHSV(HUE_BLUE, 255, 100);
         if( rightPlayer.dotPosition == 0 ) {
          rightPlayer.minFlex = rightSensorRead;
        }
      }

     FastLED.show();
      
      // When someone presses the start button, it's time to go
        leftPlayer.minFlex = leftSensorRead;
        rightPlayer.minFlex = rightSensorRead;

       if( leftPlayer.dotPosition == targetPixel - 1 && rightPlayer.dotPosition == targetPixel + 1 ) {
 //       calibrateMode = 0;
       }
      
}

void gameStart(void) {
  targetPixel = NUM_LEDS/2;
  Serial.println("game reset");
  velocity = 0;
  goalPixel = random(6,NUM_LEDS-6);
  gameState = play;
  calibrateMode = 1;
  ledUpdate(0,0);
}

void pointScored( void ) {

  for( int j=0; j<3; j++ ) {
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

