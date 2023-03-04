
//FirebaseESP8266.h must be included before ESP8266WiFi.h
#include "FirebaseESP8266.h"	// Install Firebase ESP8266 library
#include <ESP8266WiFi.h>
#define FIREBASE_HOST "harsha2-7efc2-default-rtdb.firebaseio.com/" //Without http:// or https:// schemes
#define FIREBASE_AUTH "kwBJuiP1UMCx14zLC1WLYjrxf2Li6QvozgkATVVE"
#define WIFI_SSID "HARSHA 6908"
#define WIFI_PASSWORD "123456789"

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
  if (Firebase.getString(ledData, "/FirebaseIOT/led")){
    Serial.println(ledData.stringData());
    if (ledData.stringData() == "1") {
    digitalWrite(led, HIGH);
    String t =  "reached";
     Firebase.setString(firebaseData, "/FirebaseIOT/status", t);
    }
  else if (ledData.stringData() == "0"){
    digitalWrite(led, LOW);
    String t =  "running";
     Firebase.setString(firebaseData, "/FirebaseIOT/status", t);
    }
  }
  delay(100);
}
