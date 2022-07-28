#include<Arduino.h>

#include <Wire.h>
#include <Adafruit_SSD1306.h>

#include "idol-detection.h"

#define echoPin PB3
#define trigPin PB4

volatile long duration; // variable for the duration of sound wave travel
volatile int distance; // variable for the distance measurement

volatile bool sonarInProgress = false;
volatile unsigned long sonarStartMeasureMicroS = 0;
volatile unsigned long sonarEndMeasureMicroS = 0;
volatile int consecutiveDetectTally = 0;

void triggerSonar(){
  sonarInProgress=true;
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
}

void sonarMeasure(){
  if (sonarEndMeasureMicroS >= sonarStartMeasureMicroS){
  sonarStartMeasureMicroS = micros();
  }
  else {
    sonarEndMeasureMicroS = micros();
    distance = (sonarEndMeasureMicroS-sonarStartMeasureMicroS) * 0.034 / 2;
    if (distance<30){
      consecutiveDetectTally++;
    }
    else{
    consecutiveDetectTally=0;
    }
    sonarInProgress=false;
  }
}