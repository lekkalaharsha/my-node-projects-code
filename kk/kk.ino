//VIRAL SCIENCE
//SPECIFIC TIME TRIGGER RELAY
#include <DS3231.h>

int Relay = 4;

Time t;

const int OnHour = 22; //SET TIME TO ON RELAY (24 HOUR FORMAT)
const int OnMin = 48;
const int OffHour = 22; //SET TIME TO OFF RELAY
const int OffMin = 49;

void setup() {
  Serial.begin(115200);
  rtc.begin();
  pinMode(Relay, OUTPUT);
  digitalWrite(Relay, LOW);
}

void loop() {
  t = rtc.getTime();
  Serial.print(t.hour);
  Serial.print(" hour(s), ");
  Serial.print(t.min);
  Serial.print(" minute(s)");
  Serial.println(" ");
  delay (1000);
  
  if(t.hour == OnHour && t.min == OnMin){
    digitalWrite(Relay,HIGH);
    Serial.println("LIGHT ON");
    }
    
    else if(t.hour == OffHour && t.min == OffMin){
      digitalWrite(Relay,LOW);
      Serial.println("LIGHT OFF");
    }
}
