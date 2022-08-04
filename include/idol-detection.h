extern volatile long durationLeft; // variable for the duration of sound wave travel
extern volatile int distanceLeft; // variable for the distance measurement

extern volatile long durationRight; // variable for the duration of sound wave travel
extern volatile int distanceRight; // variable for the distance measurement


extern volatile bool sonarInProgressLeft;
extern volatile unsigned long sonarStartMeasureMicroSLeft;
extern volatile unsigned long sonarEndMeasureMicroSLeft;
extern volatile int consecutiveDetectTallyLeft;

extern volatile bool sonarInProgressRight;
extern volatile unsigned long sonarStartMeasureMicroSRight;
extern volatile unsigned long sonarEndMeasureMicroSRight;
extern volatile int consecutiveDetectTallyRight;

#define CONSECUTIVE_DETECT_THRESHOLD 1
#define IDOL_SEARCH_RADIUS_CM 20

bool searchForIdolRight();
bool searchForIdolLeft();
void triggerSonar();
void sonarMeasureRight();
void sonarMeasureLeft();
void sonarSetup();
