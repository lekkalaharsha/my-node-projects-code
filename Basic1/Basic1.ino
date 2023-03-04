

#include <NTPClient.h>
// change next line to use with another board/shield
#include <ESP8266WiFi.h>
//#include <WiFi.h> // for WiFi shield
//#include <WiFi101.h> // for WiFi 101 shield or MKR1000
#include <WiFiUdp.h>
const char *ssid     = "HARSHA 6908";
const char *password = "123456789";
#define a1 D0
#define a2 D1
#define b1 D2
#define b2 D3



WiFiUDP ntpUTC;
NTPClient timeClient(ntpUTC,"in.pool.ntp.org", 19800, 60000);

void setup(){
  pinMode(LED_BUILTIN, OUTPUT);
   
  digitalWrite(LED_BUILTIN, HIGH);
  
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  
  

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();
   
}

void loop() {
 
  timeClient.update();
  Serial.println(timeClient.getHours() );

String a = timeClient.getFormattedTime();
bool b =  a > "11:50:20" && a <=  "17:34:20";




}
