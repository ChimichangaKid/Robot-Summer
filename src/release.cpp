#include "./../include/release.h"
#include "./../include/pins.h"
#include "./../include/drive.h"
#include "./../include/idol-detection.h"
#include "./../include/Tape_Track.h"

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
    drive(25, 15); // go forward slowly until detects the 10 kHz beacon
    while (!searchForIdolLeft()); // detects the 10kHz beacon
    drive(0, 0);
    delay(100);
    drive(20, -70); // steer to face the edge
    delay(500);

    bool foundEdge = false;

    while(!foundEdge) {
        if (leftReading() < LEFT_TAPE_THRESHOLD + 10 && rightReading()<RIGHT_TAPE_THRESHOLD + 10) {
            drive(30, 30);
        }
        else if (leftReading() > LEFT_TAPE_THRESHOLD + 10 && rightReading()<RIGHT_TAPE_THRESHOLD + 10) {
            drive(0, 30);
        }
        else if(leftReading() < LEFT_TAPE_THRESHOLD + 10 && rightReading()>RIGHT_TAPE_THRESHOLD + 10) {
            drive(30, 0);
        }
        else {
            foundEdge = true;
        }
    }

    // drive(30, 30); // drive forward to get to the edge
    // delay(300);

    drive(-40, -40);
    delay(340);
    drive(0, 0);
    delay(300);
    // release bridge
    Servo bridgeServo;
    bridgeServo.attach(RELEASE_SERVO);
    for(int i = 168; i >= 158; i--) {
        bridgeServo.write(i);
        delay(40);
    }
    bridgeServo.detach();
}

void releaseTrapDoor(){
    Servo trapDoorServo;
    trapDoorServo.attach(RELEASE_SERVO);
    trapDoorServo.write(0);
    delay(500);
}