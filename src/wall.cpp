#include "./../include/wall.h" 
#include "pins.h"

void driveWall(int direction);

void setUpWall(){
    /* set up limit switch */
    pinMode(WALL_LIM_SWITCH,INPUT_PULLUP);

    /* relay H-brigdes to lead screw motor */
    pinMode(RELAY_CH1, OUTPUT);
    pinMode(RELAY_CH2, OUTPUT);
    pinMode(RELAY_CH3, OUTPUT);
    digitalWrite(RELAY_CH1, HIGH);
    digitalWrite(RELAY_CH2, HIGH);
    digitalWrite(RELAY_CH3, HIGH);
}

void launchWall(){
    /* drive wall forward */
    driveWall(WALL_FORWARD);
    /* drive wall backward */
    driveWall(WALL_BACKWARD);
    delay(1000);
}

void driveWall(int direction){
    /* set up driver pins depending on direction */
    PinName HIGH_PIN = RIGHT_DRIVE_A;
    PinName LOW_PIN = RIGHT_DRIVE_B;
    if (direction == WALL_BACKWARD){
        HIGH_PIN = RIGHT_DRIVE_B;
        LOW_PIN = RIGHT_DRIVE_A;
    }

    /* drive wall */
    pwm_start(LOW_PIN, 100, 0, RESOLUTION_12B_COMPARE_FORMAT);
    pwm_start(HIGH_PIN, 100, (int)(4096 * WALL_MOTOR_DUTY_CYCLE / 100.0), RESOLUTION_12B_COMPARE_FORMAT);

    delay(4600);

    /* stop wall when limit switch is hit */
    // while (digitalRead(WALL_LIM_SWITCH));
    pwm_start(HIGH_PIN, 100, 0, RESOLUTION_12B_COMPARE_FORMAT);
}

