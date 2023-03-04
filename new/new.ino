#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#include <WiFiUdp.h>
#define FIREBASE_HOST "harsha2-7efc2-default-rtdb.firebaseio.com/" //Without http:// or https:// schemes
#define FIREBASE_AUTH "kwBJuiP1UMCx14zLC1WLYjrxf2Li6QvozgkATVVE"
const char *ssid     = "Srikanth";
const char *password = "88888888";
int a1 =D0;
int a2=D1;
int b1=D2;
int b2=D3;
int led = D5;
long trig=D7;
long echo=D6;
long Zeit;
long Strecke;
FirebaseData firebaseData;
FirebaseData ledData;

FirebaseJson json;
void setup() {
Serial.begin(9600);
pinMode(led,OUTPUT);
 pinMode(a1,OUTPUT);
    pinMode(a2,OUTPUT);
    pinMode(b1,OUTPUT);
    pinMode(b2,OUTPUT);
pinMode(trig,OUTPUT);
    pinMode(echo,INPUT);
 WiFi.begin(ssid, password);
while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
   
}

void loop() {
  Firebase.getString(ledData, "/FirebaseIOT/led");
    
  digitalWrite(trig,LOW);
  delayMicroseconds(1);
  
  digitalWrite(trig,HIGH);
  delayMicroseconds(5);
  digitalWrite(trig,LOW);
  
  Zeit = pulseIn(echo,HIGH);
  Strecke=Zeit*0.017;
  
  Serial.print(Strecke);
  
  String c =ledData.stringData();



  Serial.print(c);
if (c == "1"){
  if (   Strecke > 10){
     digitalWrite(led,HIGH);

digitalWrite(a1, HIGH);
digitalWrite(a2, LOW); 
digitalWrite(b1, HIGH);
digitalWrite(b2, LOW);
String t =  "running";
Serial.println("on");
Serial.println(t);

 Firebase.setString(firebaseData, "/FirebaseIOT/status", t);
  }
 else {
  digitalWrite(led,LOW);
digitalWrite(a1, LOW);
digitalWrite(a2,LOW); 
digitalWrite(b1, LOW);
digitalWrite(b2, LOW);
String t =  "r";
Serial.println(t);

Firebase.setString(firebaseData, "/FirebaseIOT/status", t);
   
 }
}
if (c == "0"){
 digitalWrite(led,LOW);
digitalWrite(a1, LOW);
digitalWrite(a2, LOW); 
digitalWrite(b1, LOW);
digitalWrite(b2, LOW);
String t =  "stopped";

Serial.println(t);
Firebase.setString(firebaseData, "/FirebaseIOT/status", t);
 } 
if (c == "2"){
  if (   Strecke > 10){
     digitalWrite(led,HIGH);

digitalWrite(a1, HIGH);
digitalWrite(a2, LOW); 
digitalWrite(b1, HIGH);
digitalWrite(b2, LOW);
String t =  "running";
Serial.println("on");
Serial.println(t);

 Firebase.setString(firebaseData, "/FirebaseIOT/status", t);
  }
 else {
  digitalWrite(led,LOW);
digitalWrite(a1, LOW);
digitalWrite(a2,LOW); 
digitalWrite(b1, LOW);
digitalWrite(b2, LOW);
String t =  "running";

Serial.println(t);

Firebase.setString(firebaseData, "/FirebaseIOT/status", t);
   
 }

}
}

    
