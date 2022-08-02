#include <Arduino.h>
#include <Servo.h>
#include "./../include/pins.h"
#include "./../include/bomb.h"

bool launchBombDetect(){
    // ONLY WORKS WITH RIGHT SERVO
    pinMode(BOMB_DETECT_SENSOR_RIGHT, INPUT_PULLUP);
    Servo bombServo;
    bombServo.attach(BOMB_DETECT_SERVO_RIGHT);
    bool bombDetected = false;
    for (int sweep_count = 0; sweep_count < SWEEP_COUNTS; sweep_count++){
        int servoAngle = 0;
        while(servoAngle <= 180 && !bombDetected){
            bombServo.write(servoAngle);
            bombDetected = 1 - digitalRead(BOMB_DETECT_SENSOR_RIGHT);
            servoAngle += SERVO_ANGLE_INCREASE;
            delay(SWEEP_STEP_DELAY);
        }
        bombServo.write(0);
        if (bombDetected) {
            break;
        }
    }
    return bombDetected;
    bombServo.detach();
}
