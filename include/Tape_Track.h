#include <Arduino.h>

#define TAPE_INPUT_PIN_LEFT PA4
#define TAPE_INPUT_PIN_RIGHT PA5

#define LEFT_TAPE_THRESHOLD 710
#define RIGHT_TAPE_THRESHOLD 720

#define ON_DUTY_CYCLE 50
#define TURN_DUTY_CYCLE 50
#define Kp 0.4

#define STRAIGHT 0
#define TURN_RIGHT 1
#define TURN_LEFT 2

void TapeTrack();
void setup_TapeTrack();