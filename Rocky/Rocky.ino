#include "FastLED.h"

#define NUM_LEDS 120
#define DATA_PIN 7

CRGB leds[NUM_LEDS];

float targetPixel;
int leftSensor;
int leftNormal; 
int rightSensor;
int rightNormal;
long lastDrawMillis;
long lastUpdateMillis;

float velocity;
int acceleration;
int seconds;
// gravity = 1px per second^2

void setup() {
  Serial.begin(9600);
  pinMode(3,INPUT); // left button 
  pinMode(4, INPUT); // right button
  targetPixel = 0;
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  randomSeed(analogRead(A0));
  velocity = 1;
  seconds = 0;
  lastDrawMillis = lastUpdateMillis = 0;

}

void loop() {

  if( digitalRead(3) == LOW ) leftNormal = leftSensor;
  if( digitalRead(4) == LOW) rightNormal = rightSensor;
  
  if( millis() > lastDrawMillis + 1000/30 ) { // 30 fps LED update
    ledUpdate();
    lastDrawMillis = millis();
  }

  if( millis() > lastUpdateMillis + 1000 ) {
    seconds++;
    gameUpdate();
    lastUpdateMillis = millis();
  }
}
