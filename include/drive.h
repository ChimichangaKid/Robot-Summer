#include <Arduino.h>

#define MOTOR_PWM_OUTPUT_LEFT PA_8
#define MOTOR_PWM_OUTPUT_LEFT_BACKWARDS PA_9
#define MOTOR_PWM_OUTPUT_RIGHT PB_8
#define MOTOR_PWM_OUTPUT_RIGHT_BACKWARDS PB_9

#define MOTOR_PWM_FREQUENCY_HZ 100

#define Relay2 PB12
#define Relay3 PB13
#define Relay1 PB14

void drive(int speedL, int speedR);
void drive_setup();
