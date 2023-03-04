
#include <ESP8266WiFi.h>

#include <FirebaseESP8266.h>

#include <WiFiUdp.h>
#define FIREBASE_HOST "https://home-automation-cb3f4-default-rtdb.firebaseio.com/" //Without http:// or https:// schemes
#define FIREBASE_AUTH "HA1OqOYbBDRAxmPUyZnVm6iVoko4mGyLwGzrCD5j"
const char *ssid     = "H";
const char *password = "12345678";
int a1 =D0;
int a2=D1;
#define ir1 D2
#define ir2 D3


FirebaseData firebaseData;
FirebaseData ledData;

FirebaseJson json;
void setup() {
Serial.begin(115200);

 pinMode(a1,OUTPUT);
    pinMode(a2,OUTPUT);
    pinMode(ir1,OUTPUT);
    pinMode(ir2,OUTPUT);

 WiFi.begin(ssid, password);
while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
   
}

void loop() {
  Firebase.getString(ledData, "/FirebaseIOT/cont1");
    


  String c =ledData.stringData();

  

  Serial.print(c);
if (c == "1"){
  if (  ir1 == 0){
     

digitalWrite(a1, HIGH);
digitalWrite(a2, LOW); 

String t =  "forward";
Serial.println("on");
Serial.println(t);

 Firebase.setString(firebaseData, "/FirebaseIOT/status", t);
  }
 else {

digitalWrite(a1, LOW);
digitalWrite(a2,LOW); 

String t =  "stopped";
Serial.println(t);

Firebase.setString(firebaseData, "/FirebaseIOT/status", t);
   
 }
}
if (c == "0"){

digitalWrite(a1, LOW);
digitalWrite(a2, LOW); 

String t =  "stopped";

Serial.println(t);
Firebase.setString(firebaseData, "/FirebaseIOT/status", t);
 } 
if (c == "2"){
  if ( ir2 == 0){

     

digitalWrite(a1, LOW);
digitalWrite(a2, HIGH); 

String t =  "back";
Serial.println("on");
Serial.println(t);

 Firebase.setString(firebaseData, "/FirebaseIOT/status", t);
  }
 if (  ir2 == 1){

digitalWrite(a1, LOW);
digitalWrite(a2,LOW); 

String t =  "stopped";

Serial.println(t);

Firebase.setString(firebaseData, "/FirebaseIOT/status", t);
   
 }

}
}

    
