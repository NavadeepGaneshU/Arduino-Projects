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
