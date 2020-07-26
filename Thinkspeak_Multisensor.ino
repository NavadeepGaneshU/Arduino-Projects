#include <ESP8266WiFi.h>
#include <DHT.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>
#include <Adafruit_BMP085.h>
#include <Wire.h>
#define DHTPIN 0   
//#define LDR_PIN A0
#define SOIL_PIN A0  
 
const char* ssid = "Bharu gowda"; //Your Network SSID
const char* password = "9686339191"; //Your Network Password
 
float humi;
float temp;
float moistPerc;   
//int LDRValue=0;
DHT dht(DHTPIN, DHT11);
//Adafruit_BMP085 bmp;
WiFiClient client;

unsigned long myChannelNumber = 957546; //Your Channel Number (Without Brackets)
const char * myWriteAPIKey = "LM7O5YEWP5DHGEJB"; //Your Write API Key
 
void setup()
 {
 
Serial.begin(115200);
delay(10);
dht.begin();
Serial.println("Connecting to ");
Serial.println(ssid);
 
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) 
     {
            delay(100);
            Serial.print("*");
     }
     Serial.println("");
     Serial.println("***WiFi connected***");
 ThingSpeak.begin(client);
  // initialize BMP180 sensor
  //if (!bmp.begin())
  //{
   // Serial.println("Could not find BMP180 or BMP085 sensor");
   // while (1) {}
 // }
 
}
void loop()
 {
  humi = dht.readHumidity();
  temp = dht.readTemperature();
  //LDRValue = analogRead(LDR_PIN);

//double Intensity=LDRValue*0.0048828125;
  //int lux=500/(10*((5-Vout)/Vout));//use this equation if the LDR is in the upper part of the divider
  //int lux=(2500/Intensity-500)/10;
   moistPerc = ( 100.00 - ( (analogRead(SOIL_PIN) / 1023.00) * 100.00 ) );
  
  //Serial.print("Intensity (lux): ");
  //Serial.print(lux);
     Serial.print("Temperature (*C): ");
       Serial.print(temp);
          Serial.print("Humidity (%): ");
             Serial.print(humi);
               Serial.print("Soil Moisture (%): ");
                 Serial.print(moistPerc);
     delay(1000);
ThingSpeak.setField(1, (float)temp);
ThingSpeak.setField(2, (float)humi);
//ThingSpeak.setField(3, (int)lux);
ThingSpeak.setField(4, (int)moistPerc);

ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

delay(100);
 
}
