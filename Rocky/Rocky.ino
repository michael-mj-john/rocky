#include "FastLED.h"

#define NUM_LEDS 144
#define DATA_PIN 7

CRGB leds[NUM_LEDS];

double targetPixel;
long lastDrawMillis;
float acceleration;
int frameCount;

enum gameStates { start, play, win };
gameStates gameState = start;

double velocity;
static double gravity = 1;
static double thrustMax = 4;

uint16_t framesAtTarget;
int goalPixel;

void setup() {
  Serial.begin(9600);
  pinMode(3,INPUT); // left button 
  pinMode(4, INPUT); // right button
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  randomSeed(analogRead(A5));
  frameCount = 0;
}

void loop() {

  if( gameState == start ) {
    gameStart();
  }
  if( gameState == win ) {
    pointScored();
  }
  
  if( millis() > lastDrawMillis + 1000/30 ) { // 30 fps LED update
    frameCount < 30 ? frameCount++ : frameCount = 0;
    gameUpdate();
    lastDrawMillis = millis();
  }
}

void gameStart( void ) {
  targetPixel = NUM_LEDS/2 - 5;
  Serial.println("game reset");
  velocity = 0;
  goalPixel = random(6,NUM_LEDS-6);
  gameState = play;
  do {
    acceleration = 3;
    //acceleration = random(-3,3);
  } while ( acceleration == 0 );
}

void pointScored( void ) {
  for( int i =0; i<NUM_LEDS; i++ ) {
    leds[i] = CHSV(HUE_GREEN, 255, 100);
  }
  FastLED.show();
  delay(1000);
  gameState = start;
  
}

