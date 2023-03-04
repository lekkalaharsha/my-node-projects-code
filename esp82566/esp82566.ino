#include<SoftwareSerial.h>
SoftwareSerial esp8266(10,11);
#define serialCommunicationSpeed 9600

void setup()

{
  Serial.begin(serialCommunicationSpeed);
  esp8266.begin(serialCommunicationSpeed);
  InitWifiModule();
}

void loop()
{
  if(esp8266.available())
  {
    if(esp8266.find("+IPD,"))
    {
      
    }
  }
}
