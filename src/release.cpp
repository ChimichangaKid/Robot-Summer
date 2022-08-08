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
    delay(750);
    drive(30, 30); // drive forward to get to the edge
    delay(500);

    // release bridge
    Servo bridgeServo;
    bridgeServo.attach(RELEASE_SERVO);
    bridgeServo.write(90);
}

void releaseTrapDoor(){
    Servo trapDoorServo;
    trapDoorServo.attach(RELEASE_SERVO);
    trapDoorServo.write(180);
}