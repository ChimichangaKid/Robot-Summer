#include "./../include/arms.h"
#include "./../include/pins.h"
#include "./../include/bomb.h"
// #include <Arduino.h>

void relayArms(bool mode){
    if (mode){
        digitalWrite(RELAY_CH1, HIGH);
        digitalWrite(RELAY_CH3, HIGH);
        digitalWrite(RELAY_CH2, LOW);
    } else {
        digitalWrite(RELAY_CH1, LOW);
        digitalWrite(RELAY_CH2, LOW);
    }
}

void setUpArm()
{
    /* TODO: relay H-brigdes to arms */
    pinMode(RELAY_CH1, OUTPUT);
    pinMode(RELAY_CH2, OUTPUT);
    pinMode(RELAY_CH3, OUTPUT);
    pinMode(RIGHT_DRIVE_A, OUTPUT);
    pinMode(RIGHT_DRIVE_B, OUTPUT);
    pinMode(LEFT_DRIVE_A, OUTPUT);
    pinMode(LEFT_DRIVE_B, OUTPUT);
    relayArms(true);
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

void wackArm(int side, int times){
    for (int i = 0; i < times; i++)
    {
        if (side == BOTH){
            PinName highPinR = moveArm(RIGHT, OPEN, false);
            PinName highPinL = moveArm(LEFT, OPEN, false);
            delay(OPEN_TIME);
            pwm_run(highPinR, 0);
            pwm_run(highPinL, 0);
            highPinR = moveArm(RIGHT, CLOSE,false);
            highPinL = moveArm(LEFT, CLOSE, false);
            delay(CLOSE_TIME);
            pwm_run(highPinR, 0);
            pwm_run(highPinL, 0);
        } else {
            moveArm(side,OPEN,true);
            moveArm(side,CLOSE,true);
        }
    }
}

void launchPickUp(int side){
    if (!launchBombDetect()){
        moveArm(side, OPEN, true);

        /* drives robot a bit forward*/
        /* TODO: Insert drive function. !!! MUST TURN OFF ARM RELAY */

        PinName OPPOSITE_PIN;
        if (HOLD_OPPOSITE_ARM) OPPOSITE_PIN = holdArm(1 - side);
        moveArm(side, CLOSE, true);
        
        // push statues further inside
        delay(1000);
        if (FURTHER_PUSH) wackArm(side,1);
        if (HOLD_OPPOSITE_ARM) pwm_run(OPPOSITE_PIN,0);
    }
}



