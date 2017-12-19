/*
  ARTIFICER DICE
  Britton Kroessler 2017
  
    Using an accelerometer as input for detecting when an object is tossed, 
    and generating a random number upon landing. This code can be applied
    to a die of any number--starting with 4 or 6 and working up to 20.

  NOTES: 
    Delays are pulsed to prevent stalling the accelerometer readings. 
  
  TO DO:
    Finesse Animation to coincide with tossing
    Finesse Sensing so that the random flickering will end with a singular roll.
    Basic PWM animation while in "Sleep Mode"
    Else-If statement in loop that determines roll so that the random animation can work during the toss.
      Will require a sort of recalibration.
*/

int accelState = 0; //measure movement
int lastAccelState = 0; //when object is static

int pinArray[] = {2, 3, 4, 5, 6, 7};
int count = 0;
int timer = 100;

void setup() {
  for (count=0 ; count<7 ; count++){
     pinMode(pinArray[count], OUTPUT);
  }
  Serial.begin(9600);
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

  
  //delay(100);        //Change to determine sensitivitiy of the toss, may be unnecessary...

  if(change > 50){  //Change to determine sensitivitiy
    int roll = random(2, 7+1);
    int rollStop = 0;
    
    for (count=0 ; count<7 ; count++){ //Turn all LED's ON in succession
      digitalWrite(pinArray[count], HIGH);
      delay(50);
     }
     
    delay(100); //Keep all LED's on for a moment
    
    for (count=0 ; count<7 ; count++){ //Turn all LED's OFF in succession
      digitalWrite(pinArray[count], LOW);
      delay(50);
      }
      
    for (rollStop = 0; rollStop < 20; rollStop++){ //Determine roll while continuously reading/pulsing Accelerometer
      int accelX = analogRead(A5); 
      int accelY = analogRead(A4);
      int accelZ = analogRead(A3);
      int accelState = (accelX + accelY + accelZ)/3;
      int change = abs(accelState-lastAccelState); 
      lastAccelState = accelState;
      
      digitalWrite(roll, HIGH);            //Determine's roll
      delay(100);                    //ANTI-LOCK BREAKS!
      }
    }

   //Add an else if statement to determine the roll

   else{
      for (count=0 ; count<7 ; count++){ //Turn all LED's OFF, Sleep Mode
      digitalWrite(pinArray[count], LOW);
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

