/*Sending Digital Temperature and Humidity(DHT11) sensor's data to Blynk!
https://www.clevertronics.blogspot.com
Used Hardware : ESP8266 (NodeMCU)
Used IDE : Arduino IDE 1.8.12
*/

#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <DHT.h>

char auth[] = "xxxxxxxxxxxxxxx-xxxxx"; //Enter the Auth code which was send by Blink

char ssid[] = "Your_SSID";  //Enter your WIFI Name
char pass[] = "Your_Password";  //Enter your WIFI Password

#define DHTPIN 2          // Digital pin 4

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
SimpleTimer timer;

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
 
  Blynk.virtualWrite(V5, h);  //V5 is for Humidity
  Blynk.virtualWrite(V6, t);  //V6 is for Temperature
}

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

  dht.begin();

  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
