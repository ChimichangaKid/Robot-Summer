#include <Arduino.h>

#ifndef MOTOR_PWM_FREQUENCY_HZ
#define MOTOR_PWM_FREQUENCY_HZ 100
#endif

void drive(int speedL, int speedR);
void drive_setup();
