/*
Send Temperature data to Thingspeak using SIM800 GSM and Arduino UNO.
https://www.clevertronics.blogspot.com
Used Hardware : Arduino UNO, SIM800 GSM MODULE.
Used IDE : Arduino IDE 1.8.12
*/

#include <SoftwareSerial.h>
SoftwareSerial gprsSerial(2,3);

#include <String.h>
#include <DHT.h> 

#define DHTPIN A0

DHT dht(DHTPIN, DHT11);
 
void setup()
{
  gprsSerial.begin(9600); // the GPRS baud rate 
  Serial.begin(9600);    
  dht.begin();

  delay(1000);
}
 
void loop()
{
      float h = dht.readHumidity();  //acquire data from sensor with dht library.
      float t = dht.readTemperature(); 
      delay(100);   
         
      Serial.print("Temperature = ");
      Serial.print(t);
      Serial.println(" °C");
      Serial.print("Humidity = ");
      Serial.print(h);
      Serial.println(" %");    
      
   
  if (gprsSerial.available())
    Serial.write(gprsSerial.read());

  gprsSerial.println("AT");     //AT commands used for GSM.
  delay(1000);

  gprsSerial.println("AT+CPIN?");
  delay(1000);

  gprsSerial.println("AT+CREG?");
  delay(1000);

  gprsSerial.println("AT+CGATT?");
  delay(1000);

  gprsSerial.println("AT+CIPSHUT");
  delay(1000);

  gprsSerial.println("AT+CIPSTATUS");
  delay(2000);

  gprsSerial.println("AT+CIPMUX=0");
  delay(2000);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CSTT=\"airtelmms.com\""); //start task and setting the APN. 
  delay(1000);                                     // APN is network service provider specefic.
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIICR");              //bring up wireless connection
  delay(3000);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIFSR");          
  delay(2000);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIPSPRT=0");
  delay(3000);
 
  ShowSerialData();
  
  gprsSerial.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");       //start up the Thingspeak connection
  delay(6000);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIPSEND");
  delay(4000);
  ShowSerialData();
  
  String str="GET https://api.thingspeak.com/update?api_key=EEJWSAXXXXXXXX&field1=" + String(t) +"&field2="+String(h); //enter your Thingspeak API key.
  Serial.println(str);
  gprsSerial.println(str);
  
  delay(4000);
  ShowSerialData();

  gprsSerial.println((char)26);
  delay(5000); 
  gprsSerial.println();
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIPSHUT");
  delay(100);
  ShowSerialData();
} 
void ShowSerialData()
{
  while(gprsSerial.available()!=0)
  Serial.write(gprsSerial.read());
  delay(5000); 
  
}
