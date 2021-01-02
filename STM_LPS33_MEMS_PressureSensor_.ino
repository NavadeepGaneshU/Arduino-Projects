/*
STMicroelectronics LPS33W MEMS Pressure Sensor interface with Arduino UNO!
https://www.clevertronics.blogspot.com
Used Hardware : Arduino UNO
Used IDE : Arduino IDE 1.8.12

Connection can be done through SPI or I2C. Below, SPI part is commented and I2C is used. 
For SPI Interphase:      For I2C interface:
MI--> PIN 12;            SDA - PIN A4
MO--> PIN 11;            SCL - PIN A5
CLK--> PIN 13;
CS--> PIN 10;
*/

#include <Adafruit_LPS35HW.h>
Adafruit_LPS35HW lps35hw = Adafruit_LPS35HW();

//#define LPS_CS  10 
// For software-SPI mode we need SCK/MOSI/MISO pins
//#define LPS_SCK  13
//#define LPS_MISO 12
//#define LPS_MOSI 11

void setup() 
{
  Serial.begin(9600);
 
  if (!lps35hw.begin_I2C())  //For I2C interface
  { 
  //if (!lps35hw.begin_SPI(LPS_CS))  //For SPI interface
  //  { 
  //if (!lps35hw.begin_SPI(LPS_CS, LPS_SCK, LPS_MISO, LPS_MOSI)) 
  //  {
    Serial.println("Couldn't find LPS35HW chip");
    while (1);
  }
  Serial.println("Found LPS35HW chip");
}
 
void loop() 
{
  Serial.print("Temperature: ");
  Serial.print(lps35hw.readTemperature());
  Serial.println(" C");
  
  Serial.print("Pressure: ");
  Serial.print(lps35hw.readPressure());
  Serial.println(" hPa");
 
  Serial.println();
  delay(1000);
}
