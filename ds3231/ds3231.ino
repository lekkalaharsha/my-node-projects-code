#include <config.h>
#include <ds3231.h>


#include <Wire.h>

 #define led 1
struct ts t; 
 
void setup() {
  Serial.begin(9600);
  Wire.begin();
  DS3231_init(DS3231_CONTROL_INTCN);
  pinMode (led,OUTPUT);
  /*----------------------------------------------------------------------------
  In order to synchronise your clock module, insert timetable values below !
  ----------------------------------------------------------------------------*/

 
  DS3231_set(t); 
}
 
void loop() {
  DS3231_get(&t);
  int k  =  9;
   int s  = "4" ;
  
if (k > t.hour ) {
  digitalWrite(led,HIGH);
   Serial.println("turn on");
}
else {
   Serial.println("turn off");
}
 

  delay(1000);
}
