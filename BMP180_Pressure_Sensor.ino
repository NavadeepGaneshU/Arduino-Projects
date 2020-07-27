/*
BMP180/BME180 Pressure sensor with Arduino!
https://www.clevertronics.blogspot.com
Used Hardware : Arduino UNO
Used IDE : Arduino IDE 1.8.12
Interphase : I2C [SDA-->A4, SCL-->A5]
*/

#include <SFE_BMP180.h>
#include <Wire.h>
SFE_BMP180 pressure;

void setup()
{
  Serial.begin(9600);
  if (pressure.begin())
    Serial.println("BMP180 initialised");
  else
  {
    Serial.println("BMP180 initialisation failed \n\n");
    while(1);
  }
}

void loop()
{
  char status;
  double T,P;

  status = pressure.startTemperature();
  if (status != 0)
  {
    delay(status);

    status = pressure.getTemperature(T); //getting pressure value.
    if (status != 0)
    {
      Serial.print("Temperature: ");
      Serial.print(T);
      Serial.println(" *C, ");

      status = pressure.startPressure(3);
      if (status != 0)
      {
        delay(status);

        status = pressure.getPressure(P,T); //getting temperature value.
        if (status != 0)
        {
          Serial.print("Absolute pressure: ");
          Serial.print(P);
          Serial.println(" mb ");
          Serial.println("");
        } 
      } 
    } 
  }

  delay(1000);
}
