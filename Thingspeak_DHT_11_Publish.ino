/*Sending Digital Temperature and Humidity(DHT11) sensor's data to Mathworks Thingspeak!
https://www.clevertronics.blogspot.com
Used Hardware : ESP8266 (NodeMCU)
Used IDE : Arduino IDE 1.8.12
*/

#include <DHT.h>
#include <DHT_U.h>

#include <DHT.h>  // Including library for dht

#include <ESP8266WiFi.h>
 
String apiKey = "LM7O5YEWP5DHxxxx";     //  Enter your Write API key from ThingSpeak after channel setup.

const char *ssid =  "Your_SSID";     // replace with your wifi ssid and pass key.
const char *pass =  "Your_Password";
const char* server = "api.thingspeak.com";

#define DHTPIN 0          //pin where the dht11 is connected. 
 
DHT dht(DHTPIN, DHT11);

WiFiClient client;
 
void setup() 
{
       Serial.begin(115200);
       delay(10);
       dht.begin();
 
 //Network initialisation and connection.
 
       Serial.println("Connecting......");
       Serial.println(ssid);
 
       WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected!");
 
}
 
void loop() 
{
  
      float h = dht.readHumidity();
      float t = dht.readTemperature();
      
              if (isnan(h) || isnan(t)) 
                 {
                     Serial.println("Failed to read from DHT sensor!");
                      return;
                 }

                         if (client.connect(server,80))   // "184.106.153.149" or api.thingspeak.com
                      {  
                            
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(t);
                             postStr +="&field2=";
                             postStr += String(h);
                             postStr += "\r\n\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
 
                             Serial.print("Temperature: ");
                             Serial.print(t);
                             Serial.print(" degrees Celcius, Humidity: ");
                             Serial.print(h);
                             Serial.println("%. Send to Thingspeak.");
                        }
          client.stop();
 
          Serial.println("Waiting...");
  
  // Thingspeak takes minimum 15seconds delay between updates(for free subscription).
  delay(15000);
}
