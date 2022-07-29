#include<Arduino.h>

#include <Wire.h>
#include <Adafruit_SSD1306.h>

#include "../include/idol-detection.h"
#include "../include/pins.h"

volatile long duration; // variable for the duration of sound wave travel
volatile int distance; // variable for the distance measurement

volatile bool sonarInProgress = false;
volatile unsigned long sonarStartMeasureMicroS = 0;
volatile unsigned long sonarEndMeasureMicroS = 0;
volatile int consecutiveDetectTally = 0;

bool searchForIdol(){
  if(consecutiveDetectTally>=CONSECUTIVE_DETECT_THRESHOLD){
    consecutiveDetectTally = 0;
    return true;
  }
  else{
    if (!sonarInProgress){
      triggerSonar();
      }
    return false;
  }
}

void sonarSetup(){
  pinMode(TRIGGER_PIN, OUTPUT); // Sets the TRIGGER_PIN as an OUTPUT
  pinMode(ECHO_PIN, INPUT); // Sets the echoPin as an INPUT

  //Attach external IRQ pin to IRQ handler
  attachInterrupt(digitalPinToInterrupt(ECHO_PIN), sonarMeasure, CHANGE);
}

void triggerSonar(){
  sonarInProgress=true;
  // Clears the TRIGGER_PIN condition
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  // Sets the TRIGGER_PIN HIGH (ACTIVE) for 10 microseconds
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
}

void sonarMeasure(){
  if (sonarEndMeasureMicroS >= sonarStartMeasureMicroS){
  sonarStartMeasureMicroS = micros();
  }
  else {
    sonarEndMeasureMicroS = micros();
    distance = (sonarEndMeasureMicroS-sonarStartMeasureMicroS) * 0.034 / 2;
    
    if (distance<IDOL_SEARCH_RADIUS_CM){
      consecutiveDetectTally++;
    }
    else{
    consecutiveDetectTally=0;
    }
    sonarInProgress=false;
  }
}