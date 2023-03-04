/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/
#define a1 D0
#define a2 D1
#define  b1 D2
#define  b2 D3
 
// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(a1,OUTPUT);
  pinMode(a2,OUTPUT);
   pinMode(b1,OUTPUT);
   pinMode(b2,OUTPUT);
 
   digitalWrite(a1,LOW);
   digitalWrite(a2,LOW); 
   digitalWrite(b1,LOW);
   digitalWrite(b2,LOW);
  // initialize digital pin LED_BUILTIN as an output.

}

// the loop function runs over and over again forever
void loop() {
                       // wait for a second
}
