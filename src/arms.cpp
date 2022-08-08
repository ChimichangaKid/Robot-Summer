#include "./../include/arms.h"
#include "./../include/pins.h"
#include "./../include/bomb.h"
#include "./../include/drive.h"
#include "./../include/idol-detection.h"

// #include <Arduino.h>

void relayArms(bool mode){
    if (mode){
        digitalWrite(RELAY_CH1, HIGH);
        digitalWrite(RELAY_CH2, HIGH);
        digitalWrite(RELAY_CH3, LOW);
    } else {
        digitalWrite(RELAY_CH1, LOW);
        digitalWrite(RELAY_CH2, LOW);
        digitalWrite(RELAY_CH3, LOW);
    }
}

void pwm_run(PinName Pin, int dutyCycle)
{
    pwm_start(Pin, 100, (int)(4096 * dutyCycle / 100.0), RESOLUTION_12B_COMPARE_FORMAT);
}

PinName activateArm(int side, int direction, bool timedStop, int dutyCycle)
{
    PinName HIGH_PIN;
    PinName LOW_PIN;
    PinName PIN_A = RIGHT_DRIVE_A;
    PinName PIN_B = RIGHT_DRIVE_B;
    if (side == LEFT)
    {
        PIN_A = LEFT_DRIVE_A;
        PIN_B = LEFT_DRIVE_B;
    }

    if (direction == OPEN){
        HIGH_PIN = PIN_B;
        LOW_PIN = PIN_A;
    } else {
        HIGH_PIN = PIN_A;
        LOW_PIN = PIN_B;
    }

    pwm_run(LOW_PIN, 0);
    pwm_run(HIGH_PIN, dutyCycle);

    if (timedStop)
    {
        if (direction == OPEN)
        {
            delay(OPEN_TIME);
        }
        else
        {
            delay(CLOSE_TIME);
        }
        pwm_run(HIGH_PIN, 0);
    }
    return HIGH_PIN;
}

PinName moveArm(int side, int direction, bool timedStop)
{
    return activateArm(side, direction, timedStop, ARM_SWING_DUTY_CYCLE);
}

PinName holdArm(int side)
{
    return activateArm(side, CLOSE, false, ARM_HOLD_DUTY_CYCLE);
}

void takeInProcedure(int side){
    PinName OPPOSITE_PIN;
    if (HOLD_OPPOSITE_ARM)
        OPPOSITE_PIN = holdArm(1 - side);
    moveArm(side, CLOSE, true);
    // push statues further inside
    if (FURTHER_PUSH)
    {
        delay(1000);
        wackArm(side, 1);
    }
    // delay(500);
    
    // hold close the current arm
    PinName THIS_PIN = holdArm(side);
    delay(1200);
    pwm_run(THIS_PIN, 0);
    if (HOLD_OPPOSITE_ARM)
        pwm_run(OPPOSITE_PIN, 0);
    //
    delay(500);
}

void wackArm(int side, int times){
    for (int i = 0; i < times; i++)
    {
        if (side == BOTH){
            PinName highPinR = activateArm(RIGHT, OPEN, false, WACK_BOTH_DUTY_CYCLE);
            PinName highPinL = activateArm(LEFT, OPEN, false, WACK_BOTH_DUTY_CYCLE);
            delay(OPEN_TIME);
            pwm_run(highPinR, 0);
            pwm_run(highPinL, 0);
            highPinR = activateArm(RIGHT, CLOSE, false, WACK_BOTH_DUTY_CYCLE);
            highPinL = activateArm(LEFT, CLOSE, false, WACK_BOTH_DUTY_CYCLE);
            delay(CLOSE_TIME);
            pwm_run(highPinR, 0);
            pwm_run(highPinL, 0);
        } else {
            activateArm(side, OPEN, true, ARM_SWING_DUTY_CYCLE);
            // delay(1000);
            activateArm(side, CLOSE, true, ARM_SWING_DUTY_CYCLE);
        }
    }
}

bool launchPickUpStatueOne(int side, short speed){
    drive(-25,-25);
    delay(200);
    drive(0,0);
    if (!launchBombDetectRight()){   
        delay(1000);
        relayArms(true);
        delay(1000);
        moveArm(side, OPEN, true);
        delay(1000);
        drive(speed + 55, speed);
        delay(900);
        drive(0,0);
        delay(1000);
        relayArms(true);
        delay(1000);
        takeInProcedure(side);
        return false;
    }
    else{
        return true;
    }
}

void launchPickUpStatueTwo(int side, short speed){
    drive(-25,-25);
    delay(200);
    drive(-50, 0);
    delay(750);
    drive(0, -50);
    delay(1300);
    drive(40,60);
    delay(700);
    drive(0,0);
    if (!launchBombDetectRight()){   
        delay(1000);
        relayArms(true);
        delay(1000);
        moveArm(side, OPEN, true);
        delay(1000);
        drive(39,39);
        delay(250);
        drive(0, 60);
        delay(400);
        drive(0,0);
        delay(1000);
        relayArms(true);
        delay(1000);
        takeInProcedure(side);
    }
    else{
        delay(1000);
        drive(40,40);
        delay(200);
        drive(0, 60);
        delay(450);
        drive(0,0);
        delay(1000);
    }
}

void launchPickUpStatueThree(int side, short speed){
    drive(-25,-25);
    delay(200);
    drive(0,0);
    drive(50,40);
    delay(500);
    drive(65,30);
    delay(1500);
    drive(-50, -50);
    delay(2300);
    drive(20, 20);
    drive(0, 0);
    if (!launchBombDetectLeft()){   
        delay(1000);
        relayArms(true);
        delay(1000);
        moveArm(side, OPEN, true);
        delay(1000);
        drive(speed-10, speed);
        delay(620);
        drive(0,0);
        delay(1000);
        relayArms(true);
        delay(1000);
        takeInProcedure(side);
    }
}

void launchPickUpStatueFour(int side, short speed){
    drive(-25,-25);
    delay(200);
    drive(0,0);
    delay(500);
    drive(40, 0);
    delay(600);
    drive(0,0);
    if (!launchBombDetectRight()){   
        delay(1000);
        relayArms(true);
        delay(1000);
        moveArm(side, OPEN, true);
        delay(1000);
        drive(65, 30);
        delay(800);
        drive(0,0);
        delay(1000);
        relayArms(true);
        delay(1000);
        takeInProcedure(side);
    }
}

void launchPickUpStatueFive(int side, short speed){
    drive(0,0);
    if (!launchBombDetectLeft()){   
        delay(1000);
        relayArms(true);
        delay(1000);
        moveArm(side, OPEN, true);
        delay(1000);
        drive(speed, speed);
        delay(600);
        drive(0,0);
        delay(1000);
        relayArms(true);
        delay(1000);
        takeInProcedure(side);
    }
}

