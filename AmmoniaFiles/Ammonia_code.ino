#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define RL 47  

#define m -0.263

#define b 0.42

#define Ro 20 

#define MQ_sensor A0 

#define relay1 12

LiquidCrystal_I2C lcd(0x27,16,2);


void setup() {
lcd.init();
lcd.clear();
lcd.backlight();
 pinMode(relay1, OUTPUT);
 Serial.begin(9600);

}


void loop() {

  float treshhold = 1.00;
  float VRL;

  float RS;  

  float ratio;

   

  VRL = analogRead(MQ_sensor)*(5.0/1023.0  );

  RS = ((5.0*RL)/VRL)-RL;

  ratio = RS/Ro;
 //Serial.print(ratio);
  float ppm = pow(10, ((log10(ratio)-b)/m));

  
  Serial.println(" = NH3 (ppm)"); 

  Serial.print(ppm);

  
 Serial.print(" = Voltage ");
  Serial.print(VRL);

 lcd.setCursor(0,0);
 lcd.print("Ammonia: ");
 //lcd.setCursor(5,1);
 lcd.print(VRL);
 lcd.print("ppm");
 lcd.setCursor(0,1);
 lcd.print("Voltage: ");
 lcd.print(ppm);

   delay(200);

   if(VRL > treshhold){
    digitalWrite(relay1, LOW);
   }

   else{
    digitalWrite(relay1, HIGH);
   }


}
