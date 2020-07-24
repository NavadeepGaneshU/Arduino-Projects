/*
Find soil moisture level using generic capacitive moisture sensor (3 Pins)
https://www.clevertronics.blogspot.com
Used Hardware : ESP32 by ESPRESSIF SYSTEMS
Used IDE : Arduino IDE 1.8.12
*/

const int AirValue = 0;   //Replace this value with ADC value when probe is in air(Val_1).
const int WaterValue = 3100;  //Replace this with ADC value when probe is fully dipped in water(Val_2).
int soilMoistureValue = 0;
int soilmoisturepercent=0;

const int MoistPin=35; // ADC PIN in your MCU

void setup() 
{
  Serial.begin(9600); // open serial port, set the baud rate to 9600 bps
}

void loop() 
{
soilMoistureValue = analogRead(MoistPin);  //Reads the capacitive sensor value.
  
Serial.println(soilMoistureValue); // This is pure ADC value. Use this for above 2 test cases(Val_1 and Val_2).
  
soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
  
if(soilmoisturepercent > 100)
{
  Serial.println("100 %");
}
else if(soilmoisturepercent <0)
{
  Serial.println("0 %");
}
else if(soilmoisturepercent >0 && soilmoisturepercent < 100)
{
  Serial.print(soilmoisturepercent);
  Serial.println("%");
  
}
  delay(500);
}
