#include <Arduino.h>
#include "./../include/drive.h"
#include "./../include/Tape_Track.h"
#include "./../include/pins.h"

//Variable that stores reading of reflectance value
volatile uint16_t left_reading;
volatile uint16_t right_reading;

//Record previous state in case robot drives off tape, where 0 = straight, 1 = turn right, 2 = turn left
volatile u_int8_t prev_state = 0;

//Initialize Tape Tracking
void setup_TapeTrack(){
  //Set pinmode for reading reflectance value
  pinMode(TAPE_INPUT_PIN_LEFT, INPUT);
  pinMode(TAPE_INPUT_PIN_RIGHT, INPUT);
}

//Add into Loop
void TapeTrack(int speed, int threshL, int threshR, float KP) {
  // Update the reading of the tape tracker
  left_reading = analogRead(TAPE_INPUT_PIN_LEFT);
  right_reading = analogRead(TAPE_INPUT_PIN_RIGHT);

  // Right is on tape left is not, need to turn right
  if(right_reading >= threshR && left_reading < threshL)
  {
    drive(speed, speed - (KP * (right_reading - threshR)));
    prev_state = TURN_RIGHT;
  }

  // Left is on tape right is not, need to turn left
  else if(left_reading >= threshL && right_reading < threshR)
  {
    drive(speed - (KP * (left_reading - threshL)), speed);
    prev_state = TURN_LEFT;
  }

  // Both are on the tape, turn both motors on
  else if(right_reading >= threshR && left_reading >= threshL)
  {
    drive(speed, speed);
    prev_state = STRAIGHT;
  }

  // Neither are on the tape, depend on previous state
  else if(right_reading < threshR && left_reading < threshL)
  {
    if(prev_state == STRAIGHT) {
      drive(speed, speed);
    }
    if(prev_state == TURN_RIGHT) {
      //Turn right
      drive(speed + 25, 0);
    }
    if(prev_state == TURN_LEFT) {
      //Turn left
      drive(0, speed + 25);
    }
  }
}

void find_Tape() {
  while(left_reading = analogRead(TAPE_INPUT_PIN_LEFT) < LEFT_TAPE_THRESHOLD) {
    drive(-50, 0);
  }
  drive(0, 0);
}

void find_Tape_Bomb() {
  while(left_reading = analogRead(TAPE_INPUT_PIN_LEFT) < LEFT_TAPE_THRESHOLD) {
    drive(0, 50);
  }
  drive(0, 0);
}

void find_Tape_Sweep() {
  bool found_Tape = false;
  int start = millis();
  int iteration = 0;
  while(!found_Tape){
      iteration++;
      start = millis();
  while(millis() - start < 200 * iteration && !found_Tape) {
    drive(0 ,-30);
    if(analogRead(TAPE_INPUT_PIN_RIGHT) > RIGHT_TAPE_THRESHOLD) {
      found_Tape = true;
    }
  }
    iteration++;
    start = millis();
  while(millis() - start < 200 * iteration && !found_Tape) {
    drive(-30 ,0);
    if(analogRead(TAPE_INPUT_PIN_LEFT) > LEFT_TAPE_THRESHOLD) {
      found_Tape = true;
    }
  }
  }
}