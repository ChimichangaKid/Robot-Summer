#include<Arduino.h>

#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include "idol-detection.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // This display does not have a reset pin accessible
Adafruit_SSD1306 display_handler(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

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
  }
}
