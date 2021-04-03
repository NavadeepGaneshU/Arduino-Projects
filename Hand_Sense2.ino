/* Program to control hand sanatizer system using IR hand detection sensor and SG90 servo motor
   https://robu.in/product/ir-infrared-obstacle-avoidance-sensor-module; https://robu.in/product/towerpro-sg90-9g-mini-servo-9-gram
   
   IR sensor OUT pin --> PIN8 of Arduino Nano
   Servo signal pin --> PIN9 of Arduino Nano */

#include <Servo.h>
Servo motor;
int IRSensor = 8;

void setup()
{
  Serial.begin(9600);
  motor.attach(9);
  pinMode(IRSensor, INPUT);
}

void loop()
{
  int statusSensor = digitalRead(IRSensor);
  if(statusSensor == 0)
  {
    motor.write(0);
    delay(500);
    motor.write(120);
    delay(500);
    Serial.println("It Works!");
  }
  delay(500);
}
