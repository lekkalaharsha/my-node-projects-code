#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#include <WiFiUdp.h>
#define FIREBASE_HOST "new1-bfb30-default-rtdb.firebaseio.com/" //Without http:// or https:// schemes
#define FIREBASE_AUTH "hNhtNaslkI3MW1PsWGyix94g4PM5ZZN68dqPw2tX"
const char *ssid     = "harsha";
const char *password = "1234567890";
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
FirebaseData Data;
FirebaseData Data1;
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
    Firebase.getInt(Data, "/FirebaseIOT/dis");
  digitalWrite(trig,LOW);
  delayMicroseconds(1);
  
  digitalWrite(trig,HIGH);
  delayMicroseconds(5);
  digitalWrite(trig,LOW);
  
  Zeit = pulseIn(echo,HIGH);
  Strecke=Zeit*0.017;
  
  String c =ledData.stringData();
   int  e = Data.intData();
   Serial.print(e);

  Serial.print(c);
if (  c == "1" &&  e >= 10 ){
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
if(  c == "1" &&  e < 10){
digitalWrite(led,LOW);
digitalWrite(a1, LOW);
digitalWrite(a2,LOW); 
digitalWrite(b1, LOW);
digitalWrite(b2, LOW);
String t =  "r";
Serial.println(t);

Firebase.setString(firebaseData, "/FirebaseIOT/status", t);

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
if (c == "2" &&  e >= 10){
  digitalWrite(led,HIGH);               
digitalWrite(a1, LOW);
digitalWrite(a2, HIGH); 
digitalWrite(b1,LOW);
digitalWrite(b2,HIGH);
String t =  "back";

Serial.println(t);
Firebase.setString(firebaseData, "/FirebaseIOT/status", t);
 } 
 if (c == "2" &&  e < 10){
  digitalWrite(led,LOW);
digitalWrite(a1, LOW);
digitalWrite(a2, HIGH); 
digitalWrite(b1,LOW);
digitalWrite(b2,HIGH);
String t =  "back";

Serial.println(t);
Firebase.setString(firebaseData, "/FirebaseIOT/status", t);
 } 

}

    
