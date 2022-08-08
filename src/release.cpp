#include "./../include/release.h"
#include "./../include/pins.h"
#include "./../include/drive.h"
#include "./../include/idol-detection.h"

#include <Servo.h>

void releaseBridge(){
    // navigation
    drive(-70, 20); // steer outward from rocks
    delay(700);
    drive(20, 20); // go forward slowly until detects the 10 kHz beacon
    while (!searchForIdolLeft()); // detects the 10kHz beacon
    drive(0, 0);
    delay(100);
    drive(20, -70); // steer to face the edge
    delay(900);
    drive(30, 30); // drive forward to get to the edge
    delay(500);
    drive(-30, -30);
    delay(400);
    drive(0, 0);
    delay(300);
    // release bridge
    Servo bridgeServo;
    bridgeServo.attach(RELEASE_SERVO);
    bridgeServo.write(170);
}

void releaseTrapDoor(){
    Servo trapDoorServo;
    trapDoorServo.attach(RELEASE_SERVO);
    trapDoorServo.write(0);
}