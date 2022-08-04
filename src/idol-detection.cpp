#include<Arduino.h>

#include <Wire.h>
#include <Adafruit_SSD1306.h>

#include "../include/idol-detection.h"
#include "../include/pins.h"

volatile long durationLeft; // variable for the duration of sound wave travel
volatile int distanceLeft; // variable for the distance measurement

volatile long durationRight; // variable for the duration of sound wave travel
volatile int distanceRight; // variable for the distance measurement

volatile bool sonarInProgressLeft = false;
volatile unsigned long sonarStartMeasureMicroSLeft = 0;
volatile unsigned long sonarEndMeasureMicroSLeft = 0;
volatile int consecutiveDetectTallyLeft = 0;

volatile bool sonarInProgressRight = false;
volatile unsigned long sonarStartMeasureMicroSRight = 0;
volatile unsigned long sonarEndMeasureMicroSRight = 0;
volatile int consecutiveDetectTallyRight = 0;

bool searchForIdolRight(){
  if(consecutiveDetectTallyRight>=CONSECUTIVE_DETECT_THRESHOLD){
    consecutiveDetectTallyRight = 0;
    return true;
  }
  else{
    if (!sonarInProgressRight){
      triggerSonar();
      }
    return false;
  }
}

bool searchForIdolLeft(){
  if(consecutiveDetectTallyLeft>=CONSECUTIVE_DETECT_THRESHOLD){
    consecutiveDetectTallyLeft = 0;
    return true;
  }
  else{
    if (!sonarInProgressLeft){
      triggerSonar();
      }
    return false;
  }
}

void sonarSetup(){
  pinMode(TRIGGER_PIN_RIGHT, OUTPUT); // Sets the TRIGGER_PIN as an OUTPUT
  pinMode(ECHO_PIN_RIGHT, INPUT); // Sets the echoPin as an INPUT

  pinMode(TRIGGER_PIN_LEFT, OUTPUT); // Sets the TRIGGER_PIN as an OUTPUT
  pinMode(ECHO_PIN_LEFT, INPUT); // Sets the echoPin as an INPUT
  //Attach external IRQ pin to IRQ handler
  delay(1000);
  attachInterrupt(digitalPinToInterrupt(ECHO_PIN_RIGHT), sonarMeasureRight, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ECHO_PIN_LEFT), sonarMeasureLeft, CHANGE);
  
}

void triggerSonar(){
  sonarInProgressRight=true;
  sonarInProgressLeft=true;
  // Clears the TRIGGER_PIN condition
  digitalWrite(TRIGGER_PIN_RIGHT, LOW);
  digitalWrite(TRIGGER_PIN_LEFT, LOW);
  delayMicroseconds(2);
  // Sets the TRIGGER_PIN HIGH (ACTIVE) for 10 microseconds
  digitalWrite(TRIGGER_PIN_LEFT, HIGH);
  digitalWrite(TRIGGER_PIN_RIGHT, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN_LEFT, LOW);
  digitalWrite(TRIGGER_PIN_RIGHT, LOW);
}

void sonarMeasureRight(){
  if (sonarEndMeasureMicroSRight >= sonarStartMeasureMicroSRight){
  sonarStartMeasureMicroSRight = micros();
  }
  else {
    sonarEndMeasureMicroSRight = micros();
    distanceRight = (sonarEndMeasureMicroSRight-sonarStartMeasureMicroSRight) * 0.034 / 2;

    if (distanceRight<IDOL_SEARCH_RADIUS_CM){
      consecutiveDetectTallyRight++;
    }
    else{
    consecutiveDetectTallyRight=0;
    }
    sonarInProgressRight=false;
  }
}

void sonarMeasureLeft(){
  if (sonarEndMeasureMicroSLeft >= sonarStartMeasureMicroSLeft){
  sonarStartMeasureMicroSLeft = micros();
  }
  else {
    sonarEndMeasureMicroSLeft = micros();
    distanceLeft = (sonarEndMeasureMicroSLeft-sonarStartMeasureMicroSLeft) * 0.034 / 2;

    if (distanceLeft<IDOL_SEARCH_RADIUS_CM){
      consecutiveDetectTallyLeft++;
    }
    else{
    consecutiveDetectTallyLeft=0;
    }
    sonarInProgressLeft=false;
  }
}