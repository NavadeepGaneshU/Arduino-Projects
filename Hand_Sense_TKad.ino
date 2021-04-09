/* Program for hand sanatizer system using IR hand detection sensor + Temperature detection simulation in TinkerCAD */

#include <Servo.h>    //library definitions
Servo motor1;
Servo motor2;
int IRSensor = 8;     //IR sensor input

int normalTemp = 0;   //set threshold body temperature
int celsius = 0;
int fahrenheit = 0;

void setup()
{
  pinMode(A0, INPUT);   //TMP36 sensor
  motor1.attach(9);     //sanitizer servo
  motor2.attach(11);    //flip-gate servo
  
  Serial.begin(9600);
  
  pinMode(IRSensor, INPUT);
}

void loop()
{
  
/*Body temperature and gate control part*/
  
  normalTemp = 37;    //Normal human body temp
  
  celsius = map(((analogRead(A0) - 20) * 3.04), 0, 1023, -40, 125);
  
  fahrenheit = ((celsius * 9) / 5 + 32);
  Serial.print(celsius);
  Serial.print(" C, ");
  Serial.print(fahrenheit);
  Serial.println(" F");
  
  if(celsius <= normalTemp)   //detcted temperature < normal?
  {
    motor2.write(0);
    delay(5000);
    motor2.write(90);
    delay(500);
    Serial.println("Good to go, Gate Opened!");
  }
  else            //detected temperature > normal?
  {
    Serial.println("Gate is Closed");
  }
  
/*IR hand sensor and sanitizer dispenser part*/
  
  if(digitalRead(IRSensor) == 0)  //check IR sensor status
  {
    motor1.write(0); 
    delay(500);
    motor1.write(120);
    delay(500);
    Serial.println("Sanitizer Dispensed!");
  }
  delay(500);
}
