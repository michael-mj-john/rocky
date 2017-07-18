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

double velocity;
static double thrustMax = 4;

uint16_t framesAtTarget;
int goalPixel;

Player leftPlayer;
Player rightPlayer;

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
//  Serial.println(digitalRead(2)==HIGH); // debug to test button functionality
  switch (gameState) {
    case prep:  
      preGame();    
      break;
      
    case start:
      gameStart();
      break;
      
    case win:
      pointScored();
      break;
      
    case play:
      if (millis() > lastDrawMillis + 1000/30) { // 30 fps LED update
        frameCount < 30 ? frameCount++ : frameCount = 0;
        gameUpdate();
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

      // When someone presses the start button, it's time to go
      if (digitalRead(2) == HIGH) {
        leftPlayer.minFlex = leftSensorRead;
        rightPlayer.minFlex = rightSensorRead;
  
        gameState = play;
      }
}

void gameStart(void) {
  targetPixel = NUM_LEDS/2 - 5;
  Serial.println("game reset");
  velocity = 0;
  goalPixel = random(6,NUM_LEDS-6);
  gameState = prep;
  ledUpdate(0,0);
}

void pointScored( void ) {
  for( int i =0; i<NUM_LEDS; i++ ) {
    leds[i] = CHSV(HUE_GREEN, 255, 100);
  }
  FastLED.show();
  delay(1000);
  gameState = start;
  
}

