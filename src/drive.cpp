#include <Arduino.h>
#include "./../include/drive.h"
#include "./../include/pins.h"

void drive_setup(){
/*
May be repetitive to other setup function, DOUBLE CHECK
*/

    pinMode(RELAY_CH1, OUTPUT);
    pinMode(RELAY_CH2, OUTPUT);
    pinMode(RELAY_CH3, OUTPUT);

    pinMode(LEFT_DRIVE_A, OUTPUT);
    pinMode(RIGHT_DRIVE_A, OUTPUT);
    pinMode(LEFT_DRIVE_B, OUTPUT);
    pinMode(RIGHT_DRIVE_B, OUTPUT);
}

void drive(int speedL, int speedR) {
        digitalWrite(RELAY_CH1, 0);
        digitalWrite(RELAY_CH2, 0);
        digitalWrite(RELAY_CH3, 0);

        if(speedL > 100) speedL = 100;
        if(speedL < -100) speedL = -100;
        if(speedR > 100) speedR = 100;
        if(speedR < -100) speedR = -100;

        if (speedL >= 0) {
                pwm_start(LEFT_DRIVE_B, MOTOR_PWM_FREQUENCY_HZ, 0,
                        TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
                pwm_start(LEFT_DRIVE_A, MOTOR_PWM_FREQUENCY_HZ, speedL,
                        TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
        }
        else {
                pwm_start(LEFT_DRIVE_A, MOTOR_PWM_FREQUENCY_HZ, 0,
                        TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
                pwm_start(LEFT_DRIVE_B, MOTOR_PWM_FREQUENCY_HZ, -speedL,
                        TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
        }
        if (speedR >= 0) {
                pwm_start(RIGHT_DRIVE_B, MOTOR_PWM_FREQUENCY_HZ, 0,
                        TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
                pwm_start(RIGHT_DRIVE_A, MOTOR_PWM_FREQUENCY_HZ, speedR,
                        TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
        }
        else {
                pwm_start(RIGHT_DRIVE_A, MOTOR_PWM_FREQUENCY_HZ, 0,
                        TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
                pwm_start(RIGHT_DRIVE_B, MOTOR_PWM_FREQUENCY_HZ, -speedR,
                        TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
        }
}