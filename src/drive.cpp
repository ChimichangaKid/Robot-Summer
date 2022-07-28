#include <Arduino.h>
#include "drive.h"

void drive_setup(){
/*
May be repetitive to other setup function, DOUBLE CHECK
*/

    pinMode(Relay1, OUTPUT);
    pinMode(Relay2, OUTPUT);
    pinMode(Relay3, OUTPUT);

    pinMode(MOTOR_PWM_OUTPUT_LEFT, OUTPUT);
    pinMode(MOTOR_PWM_OUTPUT_RIGHT, OUTPUT);
    pinMode(MOTOR_PWM_OUTPUT_LEFT_BACKWARDS, OUTPUT);
    pinMode(MOTOR_PWM_OUTPUT_RIGHT_BACKWARDS, OUTPUT);
}

void drive(int speedL, int speedR) {
        digitalWrite(Relay1, 0);
        digitalWrite(Relay2, 0);
        digitalWrite(Relay3, 0);

        if(speedL > 100) speedL = 100;
        if(speedL < -100) speedL = -100;
        if(speedR > 100) speedR = 100;
        if(speedR < -100) speedR = -100;

        if (speedL >= 0) {
                pwm_start(MOTOR_PWM_OUTPUT_LEFT_BACKWARDS, MOTOR_PWM_FREQUENCY_HZ, 0,
                        TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
                pwm_start(MOTOR_PWM_OUTPUT_LEFT, MOTOR_PWM_FREQUENCY_HZ, speedL,
                        TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
        }
        else {
                pwm_start(MOTOR_PWM_OUTPUT_LEFT, MOTOR_PWM_FREQUENCY_HZ, 0,
                        TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
                pwm_start(MOTOR_PWM_OUTPUT_LEFT_BACKWARDS, MOTOR_PWM_FREQUENCY_HZ, -speedL,
                        TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
        }
        if (speedR >= 0) {
                pwm_start(MOTOR_PWM_OUTPUT_RIGHT_BACKWARDS, MOTOR_PWM_FREQUENCY_HZ, 0,
                        TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
                pwm_start(MOTOR_PWM_OUTPUT_RIGHT, MOTOR_PWM_FREQUENCY_HZ, speedR,
                        TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
        }
        else {
                pwm_start(MOTOR_PWM_OUTPUT_RIGHT, MOTOR_PWM_FREQUENCY_HZ, 0,
                        TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
                pwm_start(MOTOR_PWM_OUTPUT_RIGHT_BACKWARDS, MOTOR_PWM_FREQUENCY_HZ, -speedR,
                        TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
        }
}