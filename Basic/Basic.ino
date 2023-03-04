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
FirebaseData Data1;
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
bool n = Firebase.getInt(Data1, "/FirebaseIOT/time");
bool p = Firebase.getInt(Data, "/FirebaseIOT/time1");
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
  Firebase.setString(firebaseData, "/FirebaseIOT/dis", dist);

String a = timeClient.getFormattedTime();
int v = timeClient.getHours();
int q = Data1.intData();
int w = Data.intData();
Serial.println(q);
Serial.println(w);

// (1 >   0 && v < 5 )
bool b =  (v  > q && v < w ) ;
Serial.println(v);
Serial.println(b);

String c =ledData.stringData();


  
bool d = (c == "1");
bool  e = (b || d  &&  dist > 5);
if ( e ){
digitalWrite(led,HIGH);
digitalWrite(a1, HIGH);
digitalWrite(a2, LOW); 
digitalWrite(b1, HIGH);
digitalWrite(b2, LOW);
String t =  "running";

 Firebase.setString(firebaseData, "/FirebaseIOT/status", t);
}
else{
digitalWrite(led,LOW);
digitalWrite(a1, LOW);
digitalWrite(a2, LOW); 
digitalWrite(b1, LOW);
digitalWrite(b2, LOW);
String t =  "reached";
Firebase.setString(firebaseData, "/FirebaseIOT/status", t);

}

}
