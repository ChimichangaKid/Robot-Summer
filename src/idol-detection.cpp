#include<Arduino.h>

#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // This display does not have a reset pin accessible
Adafruit_SSD1306 display_handler(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define echoPin PB3
#define trigPin PB4

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

volatile bool sonarInProgress = false;
volatile unsigned long sonarStartMeasureMicroS = 0;
volatile unsigned long sonarEndMeasureMicroS = 0;
volatile int consecutiveDetectTally = 0;

int iteration = 0;

void triggerSonar();
/**
 * @brief IRQ for external interrupt
 * @param none
 * @retval none
 */
void sonarMeasure();

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT

  //Attach external IRQ pin to IRQ handler
  attachInterrupt(digitalPinToInterrupt(echoPin), sonarMeasure, CHANGE);

  // Displays Adafruit logo by default. call clearDisplay immediately if you don't want this.
  display_handler.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display_handler.display();
  delay(2000);

  // Displays "Hello world!" on the screen
  display_handler.clearDisplay();
  display_handler.setTextSize(1);
  display_handler.setTextColor(SSD1306_WHITE);
  display_handler.setCursor(0,0);
  display_handler.println("Hello world!");
  display_handler.display();

}
void loop() {
  /**
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  **/

  if (consecutiveDetectTally>2){
    display_handler.clearDisplay();
    display_handler.setCursor(0, 0);
    display_handler.println("Treasure detected!!!");
    display_handler.display();
    delay(2000);
    display_handler.clearDisplay();
    display_handler.display();
  }
  if (!sonarInProgress){
    triggerSonar();
  iteration++;
  }
}

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