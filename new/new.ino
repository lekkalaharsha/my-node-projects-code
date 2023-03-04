#include "FirebaseESP8266.h"  // Install Firebase ESP8266 library
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
WiFiUDP ntpUTC;
NTPClient timeClient(ntpUTC,"in.pool.ntp.org", 19800, 60000);
#define FIREBASE_HOST "harsha2-7efc2-default-rtdb.firebaseio.com/" //Without http:// or https:// schemes
#define FIREBASE_AUTH "kwBJuiP1UMCx14zLC1WLYjrxf2Li6QvozgkATVVE"
#define WIFI_SSID "M202"
#define WIFI_PASSWORD "Airtel@123"
#define led D5
FirebaseData firebaseData;
FirebaseData ledData;

FirebaseJson json;
void setup()
{

  Serial.begin(115200);

  
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
Serial.println(b);
  bool c = (b > "04:00:00 "  &&  b <  "06:00:00 " );
  Serial.println(c);
  bool e =(b >= "17:25:00 "  &&  b <"22:00:00 ") ;
  Serial.println(e);
bool a = Firebase.getString(ledData, "/FirebaseIOT/led");
String s =ledData.stringData();
bool k = ( s =="1");
Serial.println(s);
  if ( c || e || k){
    digitalWrite(led, HIGH);
    Serial.println("on");
    }
 
 else {
    digitalWrite(led, LOW);
    Serial.println("OFF");
  
 }
  
 
}
