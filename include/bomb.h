////////////////////////////////////////
// Functions for bomb detection       //
////////////////////////////////////////

#ifndef SWEEP_COUNTS
#define SWEEP_COUNTS 1
#endif

#ifndef SERVO_ANGLE_INCREASE
#define SERVO_ANGLE_INCREASE -1
#endif

#ifndef SWEEP_STEP_DELAY
#define SWEEP_STEP_DELAY 20
#endif

#ifndef UPPER_LIMIT_SWEEP_LEFT
#define UPPER_LIMIT_SWEEP_LEFT 167
#endif

#ifndef UPPER_LIMIT_SWEEP_RIGHT
#define UPPER_LIMIT_SWEEP_RIGHT 13
#endif

#ifndef LOWER_LIMIT_SWEEP_LEFT
#define LOWER_LIMIT_SWEEP_LEFT 35
#endif

#ifndef LOWER_LIMIT_SWEEP_RIGHT
#define LOWER_LIMIT_SWEEP_RIGHT 160
#endif

bool launchBombDetectRight();
bool launchBombDetectLeft();