

#include <DS3231.h>

#include <Wire.h>



RTClib myRTC;

#define buz 11

int Hor;

int Min;

int Sec;




void setup()

{  

  Wire.begin();



  Serial.begin(9600);

  pinMode(buz, OUTPUT);

  

  // The following lines can be uncommented to set the date and time

  myRTC.setDOW(WEDNESDAY);     // Set Day-of-Week to SUNDAY

  myRTC.setTime(12, 0, 0);     // Set the time to 12:00:00 (24hr format)

  myRTC.setDate(1, 1, 2014);   // Set the date to January 1st, 2014

  delay(2000);

}




void loop()

{


  
}
