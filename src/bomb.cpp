#include <Arduino.h>
#include <Servo.h>
#include "./../include/pins.h"
#include "./../include/bomb.h"


bool launchBombDetectRight(){
    // ONLY WORKS WITH RIGHT SERVO
    pinMode(BOMB_DETECT_SENSOR_RIGHT, INPUT);
    delay(200);
    Servo bombServo;
    bombServo.attach(BOMB_DETECT_SERVO_RIGHT);
    bool bombDetected = false;
    for (int sweep_count = 0; sweep_count < SWEEP_COUNTS; sweep_count++){
        int servoAngle = UPPER_LIMIT_SWEEP_RIGHT;
        while(servoAngle < LOWER_LIMIT_SWEEP_RIGHT && !bombDetected){
            bombServo.write(servoAngle);
            bombDetected = 1 - digitalRead(BOMB_DETECT_SENSOR_RIGHT);
            servoAngle -= SERVO_ANGLE_INCREASE;
            delay(SWEEP_STEP_DELAY);
        }
        if (bombDetected) {
            break;
        }
    }
    bombServo.write(UPPER_LIMIT_SWEEP_RIGHT);
    delay(400);
    bombServo.detach();
    return bombDetected;
}

bool launchBombDetectLeft(){
    // ONLY WORKS WITH LEFT SERVO
    pinMode(BOMB_DETECT_SENSOR_LEFT, INPUT);
    delay(200);
    Servo bombServo;
    bombServo.attach(BOMB_DETECT_SERVO_LEFT);
    bool bombDetected = false;
    for (int sweep_count = 0; sweep_count < SWEEP_COUNTS; sweep_count++){
        int servoAngle = UPPER_LIMIT_SWEEP_LEFT;
        while(servoAngle > LOWER_LIMIT_SWEEP_LEFT && !bombDetected){
            bombServo.write(servoAngle);
            bombDetected = 1 - digitalRead(BOMB_DETECT_SENSOR_LEFT);
            servoAngle += SERVO_ANGLE_INCREASE;
            delay(SWEEP_STEP_DELAY);
        }
        if (bombDetected) {
            break;
        }
    }
    bombServo.write(UPPER_LIMIT_SWEEP_LEFT);
    delay(400);
    bombServo.detach();
    return bombDetected;
}
