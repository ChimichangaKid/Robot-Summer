extern volatile long duration; // variable for the duration of sound wave travel
extern volatile int distance; // variable for the distance measurement

extern volatile bool sonarInProgress;
extern volatile unsigned long sonarStartMeasureMicroS;
extern volatile unsigned long sonarEndMeasureMicroS;
extern volatile int consecutiveDetectTally;

void triggerSonar();
void sonarMeasure();