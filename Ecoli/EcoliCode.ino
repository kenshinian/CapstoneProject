#include <Wire.h>
#include <LiquidCrystal_I2C.h>
int lcdColumns = 7;
int lcdRows = 6;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows); 
//PH Sensor
 #define SensorPin A1      
 int relay = 2;
 int ledRelay = 3;    
unsigned long int avgValue;  
float b;
int buf[10],temp; 
//Turbidity Sensor
int sensorPin = A0;
float volt;
float ntu;
void setup() {
  pinMode(relay, OUTPUT);
  pinMode(ledRelay, OUTPUT);
  Wire.begin();
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

}

void loop() {
//PH sensro code
for(int i=0;i<10;i++)       
  { 
    buf[i]=analogRead(SensorPin);
    delay(10);
  }
  for(int i=0;i<9;i++)        
  {
    for(int j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])
      {
        temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
  avgValue=0;
  for(int i=2;i<8;i++)                     
    avgValue+=buf[i];
  float phValue=(float)avgValue*5.0/1024/6; 
  phValue=3.5*phValue - 1.3;    
  lcd.setCursor(0,0);                
  lcd.print(" pH:    ");  
  lcd.setCursor(0,9);
  lcd.print(phValue,2);
  Serial.println(phValue);
 //=====================================================================
 //Turbidity Code
 //=====================================================================
    volt = 0;
    for(int i=0; i<800; i++)
    {
        volt += ((float)analogRead(sensorPin)/1023)*5;
    }
    volt = volt/800;
    volt = round_to_dp(volt,2);
    if(volt < 2.5){
      ntu = 3000;
    }else{
      ntu = -1120.4*square(volt)+5742.3*volt-4353.8; 
    }
    lcd.setCursor(0,1);
    lcd.print(" NTU: ");
    lcd.print(ntu);

    delay(10);

if ( phValue > 7 && ntu > 500){
  digitalWrite(relay, LOW);
  digitalWrite(ledRelay, LOW);
  delay(500);
}
else{
    digitalWrite(relay, HIGH);
  digitalWrite(ledRelay, HIGH);
}
   
}
float round_to_dp( float in_value, int decimal_place )
{
  float multiplier = powf( 10.0f, decimal_place );
  in_value = roundf( in_value * multiplier ) / multiplier;
  return in_value;
}
