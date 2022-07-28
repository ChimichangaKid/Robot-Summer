#include <Arduino.h>
#include <Servo.h>
#include "./../include/pins.h"
#include "./../include/bomb.h"

bool launchBombDetect(){
    pinMode(BOMB_DETECT_SENSOR, INPUT_PULLUP);
    Servo bombServo;
    bombServo.attach(BOMB_DETECT_SERVO);
    bool bombDetected = false;
    for (int sweep_count = 0; sweep_count < SWEEP_COUNTS; sweep_count++){
        int servoAngle = 0;
        while(servoAngle <= 180 && !bombDetected){
            bombServo.write(servoAngle);
            bombDetected = 1 - digitalRead(BOMB_DETECT_SENSOR);
            servoAngle += SERVO_ANGLE_INCREASE;
            delay(SWEEP_STEP_DELAY);
        }
        if (bombDetected) {
            bombServo.write(0);
            break;
        }
    }
    return bombDetected;
}
