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
#endif
#define PIN 11

Adafruit_NeoPixel strip = Adafruit_NeoPixel(20, PIN, NEO_GRB + NEO_KHZ800);

int pixel = 0;

int accelState = 0; //measure movement
int lastAccelState = 0; //when object is static

int count = 0;

void setup() {
  Serial.begin(9600);
  pinMode(11, OUTPUT);
  strip.begin();
  strip.setBrightness(25);
  strip.show();
}

void loop() {
  int accelX = analogRead(A5); //read accelerometer pins
  int accelY = analogRead(A4);
  int accelZ = analogRead(A3);
  int accelState = (accelX + accelY + accelZ)/3; //average for troubleshooting/development
  int change = abs(accelState-lastAccelState); //this shit is important
  lastAccelState = accelState;
  Serial.print("X:");Serial.print(accelX);
    Serial.print("\t");
  Serial.print("Y:");Serial.print(accelY);
    Serial.print("\t");
  Serial.print("Z:");Serial.print(accelZ);
      Serial.print("\t");
  Serial.print("Change:"); Serial.println(change);
  strip.show();

  
  //delay(100);        //Change to determine sensitivitiy of the toss, may be unnecessary...

  if(change > 100){  //Increase to determine sensitivitiy
    int roll = random(1, 20+1);
    int rollStop = 0;

    for (count=0 ; count < 20 ; count++){ //Turn all LED's ON in succession
      strip.setPixelColor(count, 255, 255, 255);
      strip.show();
      delay(10);
     }

    delay(50); //Keep all LED's on for a moment
    
    for (count=0 ; count < 20 ; count++){ //Turn all LED's OFF in succession
      strip.setPixelColor(count, 0, 0, 0);
      strip.show();
      delay(10);
      }
      
    for (rollStop = 0; rollStop < 30; rollStop++){ //Determine roll while continuously reading/pulsing Accelerometer
      int accelX = analogRead(A5); 
      int accelY = analogRead(A4);
      int accelZ = analogRead(A3);
      int accelState = (accelX + accelY + accelZ)/3;
      int change = abs(accelState-lastAccelState); 
      lastAccelState = accelState;
      
      strip.setPixelColor(roll, 255, 255, 255);            //Determine's roll
      delay(100);                    //ANTI-LOCK BREAKS!
      strip.show();
      }
      
    for (rollStop = 0 ; count < 10 ; rollStop++){ //Turn all LED's OFF in succession
      strip.setPixelColor(roll, 0, 0, 0);
      strip.show();
      delay(100);
      }
    }

   //Add an else if statement to determine the roll

   else{
      for (count=0 ; count<20 ; count++){ //Turn all LED's OFF, Sleep Mode
      strip.setPixelColor(count, 0, 0, 0);
      strip.show();
     }
    }

  /* 
  while(change > 10){
    for (count=0 ; count<7 ; count++){
      digitalWrite(pinArray[count], LOW);}
      }
  while(change > 50){
    int roll = random(2, 7+1);
    digitalWrite(roll, HIGH);
      delay(66);
    digitalWrite(roll, LOW);
    }
   */

  /*
  if(change > 20){ //Good random animation 
    int rollAnim1 = random(2, 7+1);
    int rollAnim2 = random(2, 7+1);
    digitalWrite(rollAnim1, HIGH);
    digitalWrite(rollAnim2, HIGH);
      delay(66);
    digitalWrite(rollAnim1, LOW);
    digitalWrite(rollAnim2, LOW);
     }

   else{
     int roll = random(2, 7+1);
     int rollStop = 0;
     
     for (rollStop = 0; rollStop <= 1; rollStop++){
      digitalWrite(roll, HIGH);            //Determine's roll
      delay(1000);                    //remove delay
     }
     for (count=0 ; count<7 ; count++){
      digitalWrite(pinArray[count], LOW);
     }
    }
  /*

    /*
    for (count=0 ; count<7 ; count++){    //Turns each LED on in animation
      digitalWrite(pinArray[count], HIGH);
        delay(timer);                   //remove delay
      digitalWrite(pinArray[count], LOW);
      }
     */

    /*
     digitalWrite(roll, HIGH);            //Determine's roll
      delay(1000*2);                    //remove delay
     for (count=0 ; count<7 ; count++){
      digitalWrite(pinArray[count], LOW);
      }
    */
  
}

