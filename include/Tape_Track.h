#include <Arduino.h>

#define LEFT_TAPE_THRESHOLD 720
#define RIGHT_TAPE_THRESHOLD 720

#define Kp 0.4

#define STRAIGHT 0
#define TURN_RIGHT 1
#define TURN_LEFT 2

void TapeTrack(int speed, int threshL, int threshR, float KP);
void setup_TapeTrack();
void find_Tape();
void find_Tape_Bomb();
void find_Tape_Sweep();