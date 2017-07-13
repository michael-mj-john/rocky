#include "FastLED.h"

#define NUM_LEDS 120
#define DATA_PIN 7

CRGB leds[NUM_LEDS];

double targetPixel;
long lastDrawMillis;
float acceleration;
int frameCount;

bool greenPressed;
bool bluePressed;

enum gameStates { start, play };
gameStates gameState = start;

double velocity;
double gravity = 1;

void setup() {
  Serial.begin(9600);
  pinMode(3,INPUT); // left button 
  pinMode(4, INPUT); // right button
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  randomSeed(analogRead(A0));
  frameCount = 0;
}

void loop() {

  if( gameState == start ) {
    gameStart();
  }

  if( digitalRead(3) == LOW ) { bluePressed = 1;  } else { bluePressed = 0; }
  if( digitalRead(4) == LOW ) { greenPressed = 1; } else { greenPressed = 0; }

 // printDouble( velocity, 100 );
  
  if( millis() > lastDrawMillis + 1000/30 ) { // 30 fps LED update
    frameCount < 30 ? frameCount++ : frameCount = 0;
    gameUpdate();
    ledUpdate();
    lastDrawMillis = millis();
  }
}

void gameStart( void ) {
  targetPixel = NUM_LEDS/2;
  Serial.println("game reset");
  velocity = 0;
  gameState = play;
  do {
    acceleration = 3;
    //acceleration = random(-3,3);
  } while ( acceleration == 0 );
}

