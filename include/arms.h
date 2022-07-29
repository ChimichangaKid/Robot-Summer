#include <Arduino.h>
////////////////////////////////////////
// Functions to drive the arm         //
////////////////////////////////////////

#define LEFT 1
#define RIGHT 0
#define BOTH 2

#define OPEN 1
#define CLOSE -1

#ifndef HOLD_OPPOSITE_ARM
#define HOLD_OPPOSITE_ARM false
#endif

#ifndef FURTHER_PUSH
#define FURTHER_PUSH false
#endif

#ifndef ARM_SWING_DUTY_CYCLE
#define ARM_SWING_DUTY_CYCLE 70 // ~12V (quick as possible)
#endif

#ifndef ARM_HOLD_DUTY_CYCLE
#define ARM_HOLD_DUTY_CYCLE 35 // ~5V
#endif

#ifndef OPEN_TIME
#define OPEN_TIME 100
#endif

#ifndef CLOSE_TIME
#define CLOSE_TIME 100
#endif

void setUpArm();
void launchPickUp(int side, short);
PinName moveArm(int side, int direction, bool timedStop);
