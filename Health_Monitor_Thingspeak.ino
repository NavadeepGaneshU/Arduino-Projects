/*
Integrated health monitor and publishing data to Mathworks Thigspeak!
https://www.clevertronics.blogspot.com
Used Hardware : ESP8266 (NodeMCU)
Used IDE : Arduino IDE 1.8.12

Sensors used : DHT11 - Temperature and Humidity Sensor.
               LM19 - Body Temperature Sensor.
               BMP180 - Pressure Sensor.          
*/

#include <ESP8266WiFi.h>
#include <DHT.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>
#include <SFE_BMP180.h>
SFE_BMP180 pressure;

#define ALTITUDE 19.0 //Altitude of Kasaragod.

#include <Wire.h>
#define DHTPIN 0   
#define LM19_PIN A0

const char* ssid = "*******"; //Network SSID
const char* password = "******"; //Network Password

float humi;
float temp;  
DHT dht(DHTPIN, DHT11);
WiFiClient client;

unsigned long myChannelNumber = ******; //Thingspeak Channel Number
const char * myWriteAPIKey = "************"; //Thingspeak Write API Key
 
void setup()
 {
 
Serial.begin(9600);
delay(10);
dht.begin();
Serial.println("Connecting to ");
Serial.println(ssid);
 
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) 
     {
            delay(1000);
            Serial.print("*");
     }
     Serial.println("");
     Serial.println("***WiFi connected***");
     
 ThingSpeak.begin(client);
 
   if (pressure.begin())
    Serial.println("BMP180 init success");
  else
  {
    Serial.println("BMP180 init fail\n\n");
    while(1);
  }
 
}
void loop()
 {
  //For DHT11 sensor 
  float humi = dht.readHumidity();
  float temp = dht.readTemperature();
 
  //For LM19 temperature sensor 
  int tempvalue = analogRead(LM19_PIN);
  float millivolts = (tempvalue/1024.0) * 3300;
  float bodytemp = millivolts/10;
  
  //For BMP180 pressure sensor
  char status;
  double T,P,p0,a;
  
      status = pressure.startPressure(3);
      if (status != 0)
      {
        delay(status);
        status = pressure.getPressure(P,T);
        if (status != 0)
        {
//          Serial.print("Absolute Pressure: ");
//          Serial.print(P,2);
//          Serial.print(" mb, ");
 
          p0 = pressure.sealevel(P,ALTITUDE);
//          Serial.print(p0,2);
//          Serial.print(" mb, ");

          a = pressure.altitude(P,p0);
        }
        else Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("error starting pressure measurement\n");
  
    Serial.print("Body Temperature (*C): ");
    Serial.println(bodytemp);
     
   Serial.print("Temperature (*C): ");
   Serial.println(temp);
       
   Serial.print("Humidity (%): ");
   Serial.println(humi);
             
   Serial.print("Pressure (mb): ");
   Serial.println(P);
   
   delay(1000);

//Pushing data to cloud using API
ThingSpeak.setField(4, (float)humi);
ThingSpeak.setField(3, (float)temp);
ThingSpeak.setField(2, (int)P);
ThingSpeak.setField(1, (int)bodytemp);

ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
delay(1000);
}
