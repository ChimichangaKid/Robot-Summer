#include "./../include/wall.h"
#include "./../include/pins.h"
#include "./../include/arms.h"

void driveWall(int direction);

void setUpWall(){
    /* set up limit switch */
    pinMode(LIMIT_SWITCH_WALL, INPUT_PULLUP);  
}

void relayWall(){
    digitalWrite(RELAY_CH1, HIGH);
    digitalWrite(RELAY_CH2, HIGH);
    digitalWrite(RELAY_CH3, HIGH);
}

void useArmsToWack(int times){
    delay(1000);
    relayArms(true);
    wackArm(BOTH, times);
    moveArm(LEFT, OPEN, true);
    moveArm(RIGHT, OPEN, true);
}

void launchWall(){
    /* wack arms*/
    relayWall();
    driveWall(WALL_BACKWARD);
    delay(1000);
    useArmsToWack(2);
    /* relay motor to wall */
    delay(1000);
    relayWall();
    /* drive wall forward */
    driveWall(WALL_FORWARD);
    delay(3000);
    /* drive wall backward */
    driveWall(WALL_BACKWARD);
    delay(1000);
}

void driveWall(int direction){
    /* set up driver pins depending on direction */
    PinName HIGH_PIN = RIGHT_DRIVE_B;
    PinName LOW_PIN = RIGHT_DRIVE_A;
    if (direction == WALL_BACKWARD){
        HIGH_PIN = RIGHT_DRIVE_A;
        LOW_PIN = RIGHT_DRIVE_B;
    }

    /* drive wall */
    pwm_start(LOW_PIN, 100, 0, RESOLUTION_12B_COMPARE_FORMAT);
    pwm_start(HIGH_PIN, 100, (int)(4096 * WALL_MOTOR_DUTY_CYCLE / 100.0), RESOLUTION_12B_COMPARE_FORMAT);

    
    if (direction == WALL_FORWARD){
        int totalTime = 5000;
        int intermediateStopTime = 2500;
        delay(intermediateStopTime);
        pwm_start(HIGH_PIN, 100, 0, RESOLUTION_12B_COMPARE_FORMAT);

        // useArmsToWack(1);

        delay(1000);
        relayWall();
        delay(1000);
        // pwm_start(LOW_PIN, 100, 0, RESOLUTION_12B_COMPARE_FORMAT);
        pwm_start(HIGH_PIN, 100, (int)(4096 * WALL_MOTOR_DUTY_CYCLE / 100.0), RESOLUTION_12B_COMPARE_FORMAT);
        delay(totalTime-intermediateStopTime);
    }
    
    /* FOR BACKWARD: stop wall when limit switch is hit */
    if (direction == WALL_BACKWARD){
        while (digitalRead(LIMIT_SWITCH_WALL));
    }
    
    pwm_start(HIGH_PIN, 100, 0, RESOLUTION_12B_COMPARE_FORMAT);
}

