#define a D0
void setup() {
  pinMode(a,OUTPUT);

}

void loop() {
  
digitalWrite(a, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(a, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);  
}
