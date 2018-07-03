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

int accelState = 0; //measure movement
int lastAccelState = 0; //when object is static

int count = 0;

unsigned int changes [] = {0, 0, 0, 0};
int index = 0;

void setup() {
  Serial.begin(9600);
  pinMode(9, OUTPUT); //Accelerometer Power
  pinMode(10, OUTPUT); //Neopixel Power
  pinMode(11, OUTPUT); //Neopixel Signal
  strip.begin();
  strip.setBrightness(100);
  strip.show();
}

void loop() {
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH); //add MOSFET or switch to battery power for Neopixels
  for(int i = 0; i < 2 ; i++){
    changes[i] = readAccel();
  }

  //  Serial.print("X:");Serial.print(accelX);    //print debugging
  //    Serial.print("\t");
  //  Serial.print("Y:");Serial.print(accelY);
  //    Serial.print("\t");
  //  Serial.print("Z:");Serial.print(accelZ);
  //      Serial.print("\t");
  //  Serial.print("Change:"); Serial.println(change);
  strip.show();


  //delay(100);        //Change to determine sensitivitiy of the toss, may be unnecessary...

  if ((changes[0] > 30) && (changes[1] > 30)) { //Increase to determine sensitivitiy
    int roll = (TrueRandom.random(1, 21));
    int rollStop = 0;

    for (count = 0 ; count < 20 ; count++) { //Turn all LED's ON in succession
      strip.setPixelColor(count, 255, 255, 255);
      strip.show();
      delay(10);
    }

    delay(50); //Keep all LED's on for a moment

    for (count = 0 ; count < 20 ; count++) { //Turn all LED's OFF in succession
      strip.setPixelColor(count, 0, 0, 0);
      strip.show();
      delay(10);
    }

    for (rollStop = 0; rollStop < 30; rollStop++) { //Determine roll while continuously reading/pulsing Accelerometer
      int accelX = analogRead(A5);
      int accelY = analogRead(A4);
      int accelZ = analogRead(A3);
      int accelState = (accelX + accelY + accelZ) / 3;
      int change = abs(accelState - lastAccelState);
      lastAccelState = accelState;

      strip.setPixelColor(roll, 255, 255, 255);            //Determine's roll
      delay(100);                    //ANTI-LOCK BREAKS!
      strip.show();
    }

    for (rollStop = 0 ; count < 10 ; rollStop++) { //Turn all LED's OFF in succession
      strip.setPixelColor(roll, 0, 0, 0);
      strip.show();
      delay(100);
    }
  }

  //Add an else if statement to determine the roll

  else {
    for (count = 0 ; count < 20 ; count++) { //Turn all LED's OFF, Sleep Mode
      strip.setPixelColor(count, 0, 0, 0);
      strip.show();
    }
  }
}

int readAccel() {
  int accelX = analogRead(A5); //read accelerometer pins
  int accelY = analogRead(A4);
  int accelZ = analogRead(A3);
  int accelState = (accelX + accelY + accelZ) / 3; //average for troubleshooting/development
  int change = abs(accelState - lastAccelState); //this shit is important
  lastAccelState = accelState;

  return change;
}

