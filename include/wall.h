#include <Arduino.h>

////////////////////////////////////////
// Functions to drive the moving wall //
////////////////////////////////////////

#define WALL_MOTOR_DUTY_CYCLE 45 // about 11V

#define WALL_FORWARD 1
#define WALL_BACKWARD -1

void launchWall();
void driveWall(int direction);
void setUpWall();