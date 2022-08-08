////////////////
//  INCLUDES  //
////////////////

#include "../include/drive.h"
#include "../include/Tape_Track.h"
#include "../include/idol-detection.h"
#include "./../include/arms.h"
#include "../include/infrared.h"
#include "../include/wall.h"
#include "../include/bomb.h"
#include "../include/release.h"

#include <Arduino.h>

#define STATE_TAPE_TRACK 1
#define STATE_IR_1KHZ 2
#define STATE_IR_10KHZ 3
#define STATE_ON_BRIDGE 4
#define STATE_DROP_OFF 5

#define DEFAULT_SPEED 25

void setup() {
    drive_setup();
    setup_TapeTrack();
    sonarSetup();
    setUpWall();
}

short statues_seen = 0;
float error;
float ir_pid;
bool is_turned = false;
short current_state = STATE_TAPE_TRACK;
bool bombdetected = false;
float timeSinceBomb;
bool course_finished = false;

void loop() {
  
  if(current_state == STATE_TAPE_TRACK){
    TapeTrack();
  }
  
  if(current_state == STATE_IR_1KHZ){
    error = getDifferenceInIRReadings(ONE_KHZ);
    ir_pid = infraredPIDControl(error);
    infraredDrive(error, ir_pid);
  }

  if(current_state == STATE_IR_10KHZ){    
    error = getDifferenceInIRReadings(TEN_KHZ);
    ir_pid = infraredPIDControl(error);
    infraredDrive(error, ir_pid);
  }

  if(current_state == STATE_ON_BRIDGE){
    // tape track at lower speed
    // for some time
  }

  if (current_state == STATE_DROP_OFF){
    drive(30,30);
    while(!searchForIdolRight()); // drive forward until right sensor detects the pole
    drive(0,0);
    delay(200); 
    drive(20,20); // drive further forward to peak beyond the edge
    delay(500);
    releaseTrapDoor();
    delay(500);
    launchWall();
    course_finished = true;
    delay(120000);
  }
if(bombdetected){
  if(millis() - timeSinceBomb == 3000){
    bombdetected = false;
  }
}
else{
  if(searchForIdolRight()){
    switch(statues_seen){
      case 0: // FIRST STATUE PICKUP
          bombdetected = launchPickUpStatueOne(RIGHT, DEFAULT_SPEED);
          if (!bombdetected){
            drive(-70, -10);
            delay(1000);
            find_Tape();
            drive(-50, 0);
            delay(240);
            drive(50, 50);
            delay(2700);
            drive(0, -60);
            find_Tape_Sweep();
          }
          else{
            timeSinceBomb = millis();
            find_Tape_Bomb();
            drive(0, 50);
            delay(270);
            drive(50, 50);
            delay(2000);
            find_Tape_Sweep();
          }
          statues_seen += 1;
          break;
      case 1: // SECOND STATUE PICKUP
          launchPickUpStatueTwo(RIGHT, DEFAULT_SPEED);
          find_Tape();
          drive(40, 65);
          delay(450);
          drive(30, 30);
          while(!searchForIdolLeft());
          drive(40,50);
          delay(500);
          drive(0,0);
          locateBeacon(ONE_KHZ, LEFT);
          current_state = STATE_IR_1KHZ;
          statues_seen += 1;
          statues_seen += 1;
          break;
      
      case 4: // FOURTH STATUE PICKUP
          launchPickUpStatueFour(RIGHT, DEFAULT_SPEED);
          releaseBridge(); // navigation included
          current_state = STATE_ON_BRIDGE;
          statues_seen += 1;
          break;
      }
    }

  if(searchForIdolLeft()){
    switch(statues_seen){
      case 2: // DETECTS THE ARCHWAY (CANNOT AVOID)
          drive(40,50);
          delay(600);
          drive(0,0);
          locateBeacon(ONE_KHZ, LEFT);
          current_state = STATE_IR_1KHZ;
          statues_seen += 1;
          break;
      case 3: // THIRD STATUE PICKUP
          launchPickUpStatueThree(LEFT, 50);
          drive(70,30);
          delay(1200);
          locateBeacon(TEN_KHZ, LEFT);
          current_state = STATE_IR_10KHZ;
          statues_seen += 1;
          break;
      case 5: // FIFTH STATUE PICKUP
          launchPickUpStatueFive(LEFT, DEFAULT_SPEED);
          current_state = STATE_DROP_OFF;
          statues_seen += 1;
          break;
    }
    
  }
}
}

// void loop(){
//   launchWall();
//   delay(500);
// }