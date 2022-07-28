extern volatile long duration; // variable for the duration of sound wave travel
extern volatile int distance; // variable for the distance measurement

extern volatile bool sonarInProgress;
extern volatile unsigned long sonarStartMeasureMicroS;
extern volatile unsigned long sonarEndMeasureMicroS;
extern volatile int consecutiveDetectTally;

#define CONSECUTIVE_DETECT_THRESHOLD 5
#define IDOL_SEARCH_RADIUS_CM 15

bool searchForIdol();
void triggerSonar();
void sonarMeasure();
void sonarSetup();
