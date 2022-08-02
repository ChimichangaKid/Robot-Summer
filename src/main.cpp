////////////////
//  INCLUDES  //
////////////////

#include "../include/drive.h"
#include "../include/Tape_Track.h"
#include "../include/idol-detection.h"
#include "./../include/arms.h"
#include "../include/infrared.h"
#include "../include/wall.h"


#include <Arduino.h>


#define STATE_TAPE_TRACK 0
#define STATE_IR_1KHZ 3
#define STATE_IR_10KHZ 4
#define STATE_PICKUP -1

#define DEFAULT_SPEED 25


void setup() {
    drive_setup();
    setup_TapeTrack();
    sonarSetup();
}

short statues_seen = 0;
float error;
float ir_pid;
bool is_turned = false;

void loop() {
  

  //if(statues_seen == STATE_TAPE_TRACK){
    TapeTrack();
  //}
  
  /*
  if(statues_seen == STATE_IR_1KHZ){
    error = getDifferenceInIRReadings(ONE_KHZ);
    ir_pid = infraredPIDControl(error);
    infraredDrive(error, ir_pid);
  }

  if(statues_seen == STATE_IR_10KHZ){
    if(!is_turned){
      locateBeacon(TEN_KHZ);
      is_turned = true;
    }
    
    error = getDifferenceInIRReadings(TEN_KHZ);
    ir_pid = infraredPIDControl(error);
    infraredDrive(error, ir_pid);
  }
  */

  //if(!(statues_seen == STATE_PICKUP)){
    if(searchForIdol()){
      
      switch(statues_seen){
        case 0:
          launchPickUpStatueOne(RIGHT, DEFAULT_SPEED);
          find_Tape();
          break;
        case 1:
          launchPickUpStatueTwo(RIGHT, DEFAULT_SPEED);
          find_Tape();
      }
      
      statues_seen += 1;
      
    }
  //}
  
  
}
