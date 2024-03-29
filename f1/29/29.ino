#include <NTPClient.h>
#include "FirebaseESP8266.h"

// change next line to use with another board/shield
#include <ESP8266WiFi.h>
//#include <WiFi.h> // for WiFi shield
//#include <WiFi101.h> // for WiFi 101 shield or MKR1000
#include <WiFiUdp.h>
#define FIREBASE_HOST "harsha2-7efc2-default-rtdb.firebaseio.com/" //Without http:// or https:// schemes
#define FIREBASE_AUTH "kwBJuiP1UMCx14zLC1WLYjrxf2Li6QvozgkATVVE"    
const char *ssid     = "HARSHA 6908";
const char *password = "123456789";
#define a1 D0
#define a2 D1
#define  b1 D2
#define  b2 D3
 
#define SOUND_VELOCITY 0.034
#define CM_TO_INCH 0.393701
#define trigPin  D4
#define echoPin D6
long duration;
int dist;

#define led D5


WiFiUDP ntpUTC;
NTPClient timeClient(ntpUTC,"in.pool.ntp.org", 19800, 60000);
FirebaseData firebaseData;
FirebaseData ledData;
FirebaseData Data;
FirebaseJson json;


void setup(){
  Serial.begin(115200);
  pinMode(a1,OUTPUT);
pinMode(a2,OUTPUT);
   pinMode(b1,OUTPUT);
   pinMode(b2,OUTPUT);
   pinMode(led,OUTPUT);
 pinMode(trigPin, OUTPUT); 
 pinMode(echoPin, INPUT);
     
  

  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  timeClient.begin();
}

void loop() {
  timeClient.update();
   bool m = Firebase.getString(ledData, "/FirebaseIOT/led");
      bool n = Firebase.getString(Data, "/FirebaseIOT/in");

  
   digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  dist=(duration*0.034/2);
  Serial.print("Distance (cm): ");
  Serial.println(dist);

String a = timeClient.getFormattedTime();

bool b =  (a > "01:00:20" && a <=  "05:00:20") ;
  String c =ledData.stringData();
bool d = (c == "1");
bool  e = (b || d  &&  dist < 5 );
bool f =e ;
Serial.println(c);
  int l = timeClient.hour();
  Serial.println(l);
int p =timeClient.hour();
Serial.println(p);


if ( e ){
digitalWrite(led,LOW);
digitalWrite(a1, HIGH);
digitalWrite(a2, LOW); 
digitalWrite(b1, HIGH);
digitalWrite(b2, LOW);
}
else{
digitalWrite(led,HIGH);
digitalWrite(a1, LOW);
digitalWrite(a2, LOW); 
digitalWrite(b1, LOW);
digitalWrite(b2, LOW);
}

}
