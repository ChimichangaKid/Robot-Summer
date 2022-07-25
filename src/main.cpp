#include<Arduino.h>
#include<Servo.h>

#define BOMB_DETECT PB12
int SERVO_PIN = A0;
int servoAngle = 0;

Servo myServo;

void setup()
{
  pinMode(BOMB_DETECT, INPUT_PULLUP);
  myServo.attach(SERVO_PIN);
}

void loop()
{
  if (servoAngle>180 || digitalRead(BOMB_DETECT) == 0){
    servoAngle = 0;
  }
  myServo.write(servoAngle);
  delay(100);
  servoAngle+=6;
}
