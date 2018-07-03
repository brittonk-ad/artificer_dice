/*
  ARTIFICER DICE
  Britton Kroessler 2017

    Using an accelerometer as input for detecting when an object is tossed,
    and generating a random number upon landing. Uses Breadboard-friendly Neopixels,
    may later incorporate more colorful animations.

  NOTES:
    Delays are pulsed to prevent stalling the accelerometer readings.

  TO DO:
    Low Power Code: Check every 3 seconds for change?
    Finesse Animation to coincide with tossing
    Basic PWM animation while in "Sleep Mode"
    Else-If statement in loop that determines roll so that the random animation can work during the toss.
      Will require a sort of recalibration.
    Low-pass Filter: Removing noise
*/

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#include <TrueRandom.h>
#endif
#define PIN 11

Adafruit_NeoPixel strip = Adafruit_NeoPixel(20, PIN, NEO_GRB + NEO_KHZ800);

int pixel = 0;
unsigned long previousMillis = 0;
long onCycle = 0;
long offCycle = 2;

void setup() {
  Serial.begin(9600);
  pinMode(9, OUTPUT); //Accelerometer Power
  pinMode(10, OUTPUT); //Neopixel Power
  pinMode(11, OUTPUT); //Neopixel Signal
  strip.begin();
//  strip.setBrightness(255);
  strip.show();
}

void loop() {
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH); //add MOSFET or switch to battery power for Neopixels
  int light1 = (TrueRandom.random(0,21));
  int light2 = (TrueRandom.random(0,21));
  int light3 = (TrueRandom.random(0,21));
  int light4 = (TrueRandom.random(0,21));
  int light5 = (TrueRandom.random(0,21));

  int b = 0;


  for(b = 0; b <= 255; b++){
    strip.setPixelColor(light1, 100, 200, 255);
    strip.setPixelColor(light2, 100, 200, 255);
    strip.setPixelColor(light3, 100, 200, 255);
    strip.setPixelColor(light4, 100, 200, 255);
    strip.setPixelColor(light5, 100, 200, 255);
    strip.setBrightness(b);
    strip.show();
    delay(0);
  }  
  
  for(b = 255; b <=255; b--){
    strip.setPixelColor(light1, 80, 175, 255);
    strip.setPixelColor(light2, 80, 175, 255);
    strip.setPixelColor(light3, 80, 175, 255);
    strip.setPixelColor(light4, 80, 175, 255);
    strip.setPixelColor(light5, 80, 175, 255);
    strip.setBrightness(b);
    strip.show();
    delay(2);
    if(b < 0){
      break; //THIS SHIT RIGHT HERE FUCK YEAH!
    }
  }
}

void idle(){
  
}

void sm_idle(){
  
}

