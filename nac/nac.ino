#include "FirebaseESP8266.h"  // Install Firebase ESP8266 library
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
WiFiUDP ntpUTC;
NTPClient timeClient(ntpUTC,"in.pool.ntp.org", 19800, 60000);
#define FIREBASE_HOST "harsha2-7efc2-default-rtdb.firebaseio.com/" //Without http:// or https:// schemes
#define FIREBASE_AUTH "kwBJuiP1UMCx14zLC1WLYjrxf2Li6QvozgkATVVE"
#define WIFI_SSID "H"
#define WIFI_PASSWORD "12345678"
int led = D5;  
FirebaseData firebaseData;
FirebaseData ledData;

FirebaseJson json;
void setup()
{

  Serial.begin(9600);

  
  pinMode(led,OUTPUT);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

}
void loop() {

  timeClient.update();

  String b = timeClient.getFormattedTime();
  bool c = b >  "4:00:00 "  &&  b <  "6:00:00 " ;
  bool e =b >  "18:00:00 "  &&  b <"22:00:00 " ;
  String l =ledData.stringData();
  

  int a = Firebase.getString(ledData, "/FirebaseIOT/led");
Serial.println(a);
Serial.println(b);
  if ( c || b || (l="1")){
    digitalWrite(led, HIGH);
    Serial.println("on1");
    }
 elseif| b || (l="0")){
  digitalWrite(led, LOW);
    Serial.println("OFF");
    }
 else {
    digitalWrite(led, LOW);
    Serial.println("OFF");
  
 }
  
 
}
