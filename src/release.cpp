#include "./../include/release.h"
#include "./../include/pins.h"
#include "./../include/drive.h"
#include "./../include/idol-detection.h"

#include <Servo.h>

void releaseSetup() {
    Servo bridgeServo;
    bridgeServo.attach(RELEASE_SERVO);
    bridgeServo.write(175);
    bridgeServo.detach();
}

void releaseBridge(){
    // navigation
    drive(-20, 0);
    delay(100);
    drive(25, 20); // go forward slowly until detects the 10 kHz beacon
    while (!searchForIdolLeft()); // detects the 10kHz beacon
    drive(0, 0);
    delay(100);
    drive(20, -70); // steer to face the edge
    delay(800);
    drive(30, 30); // drive forward to get to the edge
    delay(500);
    drive(-40, -40);
    delay(400);
    drive(0, 0);
    delay(300);
    // release bridge
    Servo bridgeServo;
    bridgeServo.attach(RELEASE_SERVO);
    bridgeServo.write(165);
}

void releaseTrapDoor(){
    Servo trapDoorServo;
    trapDoorServo.attach(RELEASE_SERVO);
    trapDoorServo.write(0);
}