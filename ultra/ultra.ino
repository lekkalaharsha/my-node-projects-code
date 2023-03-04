#define SOUND_VELOCITY 0.034
#define CM_TO_INCH 0.393701
#define trigPin  D4
#define echoPin D6
long duration;
float dist;
float distanceInch;
#define led D5



void setup() {
    Serial.begin(115200);
     
       pinMode(led,OUTPUT);
       pinMode(trigPin, OUTPUT); 
 pinMode(echoPin, INPUT);
  digitalWrite(led,LOW);
 

}

void loop() {
  
   digitalWrite(trigPin, LOW);
  delayMicroseconds(0.5);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(2);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  dist= duration * SOUND_VELOCITY/2;
  
  // Convert to inches
 
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(dist);
  if (  dist < 10 ){
   digitalWrite(led,LOW);
  
  
}
else{
     digitalWrite(led,HIGH);
  
  
  
}
 

}
