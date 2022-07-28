#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include "./../include/wall.h"
#include "./../include/arms.h"

void setup() {
  // put your setup code here, to run once:
  setUpWall();
}

void loop() {
  // put your main code here, to run repeatedly:
  launchWall();
  // launchPickUp(RIGHT);
  // driveWall(WALL_BACKWARD);
  delay(2000);
}