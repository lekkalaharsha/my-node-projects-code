#include <LiquidCrystal_I2C.h>


int lcdColumns =16;
int lcdRows =2;
int pin1=A0;
int pin2=A5;
int pin3=A2;
int average;
int sensorValue1 =0;
LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
    Serial.begin(9600); 
  lcd.init();                      // initialize the lcd 
pinMode(pin1,OUTPUT);

  lcd.backlight();
                
}


void loop()
{
     sensorValue1  = analogRead(pin1);
   int sensorValue2 = analogRead(pin2);
   int sensorValue3= analogRead(pin3);
    
  float  average1=(pin1)/2;
  float  average2=(pin2)/2;
  float  average3=(pin3)/2;
float averages =average1+average3+average2;
  float voltage1 = average1 * (5.0 / 1023.0); 
float voltage2 = average2*(5.0 / 1023.0); 
float voltage3 = average3* (5.0 / 1023.0); 
float voltages = voltage1 + voltage2 + voltage3 ;
  Serial.println(sensorValue1 ); 
   lcd.setCursor(0,0);
  lcd.print(sensorValue1);
 delay(100);
lcd.setCursor(1,1);
lcd.print(averages);
Serial.println(averages);

}
