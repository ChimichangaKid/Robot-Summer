////////////////////////////////////////
// Functions for bomb detection       //
////////////////////////////////////////

#ifndef SWEEP_COUNTS
#define SWEEP_COUNTS 1
#endif

#ifndef SERVO_ANGLE_INCREASE
#define SERVO_ANGLE_INCREASE -5
#endif

#ifndef SWEEP_STEP_DELAY
#define SWEEP_STEP_DELAY 100
#endif

#ifndef UPPER_LIMIT_SWEEP
#define UPPER_LIMIT_SWEEP 167
#endif

#ifndef LOWER_LIMIT_SWEEP
#define LOWER_LIMIT_SWEEP 40
#endif

bool launchBombDetect();