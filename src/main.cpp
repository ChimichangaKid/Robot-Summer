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


#include <Arduino.h>


#define STATE_TAPE_TRACK 1
#define STATE_IR_1KHZ 2
#define STATE_IR_10KHZ 3

#define DEFAULT_SPEED 25


void setup() {
    drive_setup();
    setup_TapeTrack();
    sonarSetup();
}

short statues_seen = 2;
float error;
float ir_pid;
bool is_turned = false;
short current_state = STATE_TAPE_TRACK;

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
  

  if(searchForIdol()){
    switch(statues_seen){
      case 0: // FIRST STATUE PICKUP
          launchPickUpStatueOne(RIGHT, DEFAULT_SPEED);
          find_Tape();
          break;
      case 1: // SECOND STATUE PICKUP
          launchPickUpStatueTwo(RIGHT, DEFAULT_SPEED);
          find_Tape();
          break;
      case 2: // DETECTS THE ARCHWAY (CANNOT AVOID)
          current_state = STATE_IR_1KHZ;
          break;
      case 3: // THIRD STATUE PICKUP
          launchPickUpStatueThree(LEFT, DEFAULT_SPEED);
          locateBeacon(TEN_KHZ);
          current_state = STATE_IR_10KHZ;
          break;
      case 4: // FOURTH STATUE PICKUP
          break;
      }
      
      //statues_seen += 1;
      
    }
  //}
  
  
}
