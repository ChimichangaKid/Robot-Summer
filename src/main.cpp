<<<<<<< HEAD
#include <Arduino.h>
=======
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display_handler(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define TAPE_INPUT_PIN_LEFT PA4 // Tape Tracking Pins
#define TAPE_INPUT_PIN_RIGHT PA5

#define LEFT_TAPE_THRESHOLD 710
#define RIGHT_TAPE_THRESHOLD 720

#define MOTOR_PWM_OUTPUT_LEFT PA_8
#define MOTOR_PWM_OUTPUT_LEFT_BACKWARDS PA_9
#define MOTOR_PWM_OUTPUT_RIGHT PB_8
#define MOTOR_PWM_OUTPUT_RIGHT_BACKWARDS PB_9

#define Relay2 PB12
#define Relay3 PB13
#define Relay1 PB14

#define MOTOR_PWM_FREQUENCY_HZ 100
#define ON_DUTY_CYCLE 50
#define TURN_DUTY_CYCLE 50
#define Kp 0.4

// Digital Read Readings
volatile uint16_t left_reading;
volatile uint16_t right_reading;

volatile u_int8_t prev_state = 0;

void drive(int speedL, int speedR);
>>>>>>> 2cc11e0 (Working tuned TP code)

void setup() {
<<<<<<< HEAD
  // put your setup code here, to run once:
=======
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  pinMode(Relay3, OUTPUT);

  // Setup Input tape track pins
  pinMode(TAPE_INPUT_PIN_LEFT, INPUT);
  pinMode(TAPE_INPUT_PIN_RIGHT, INPUT);

  // Setup output pwm motor pins
  pinMode(MOTOR_PWM_OUTPUT_LEFT, OUTPUT);
  pinMode(MOTOR_PWM_OUTPUT_RIGHT, OUTPUT);
  pinMode(MOTOR_PWM_OUTPUT_LEFT_BACKWARDS, OUTPUT);
  pinMode(MOTOR_PWM_OUTPUT_RIGHT_BACKWARDS, OUTPUT);

  // Initializes Display
  display_handler.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display_handler.display();
  delay(2000);

  display_handler.clearDisplay();
  display_handler.setTextSize(1);
  display_handler.setTextColor(SSD1306_WHITE);
  display_handler.setCursor(0,0);
  display_handler.println("Hello world!");
  display_handler.display();
>>>>>>> 0d061f0 (Implemented relay to drive function)
}

void loop() {
<<<<<<< HEAD
<<<<<<< HEAD
  // put your main code here, to run repeatedly:
} 
=======
  // Update the reading of the tape tracker
  left_reading = analogRead(TAPE_INPUT_PIN_LEFT);
  right_reading = analogRead(TAPE_INPUT_PIN_RIGHT);

  display_handler.clearDisplay();
  display_handler.setCursor(0,0);
  display_handler.println(left_reading);
  display_handler.setCursor(0,10);
  display_handler.println(right_reading);
  display_handler.display();

  // Right is on tape left is not, need to turn right
  if(right_reading > RIGHT_TAPE_THRESHOLD && left_reading < LEFT_TAPE_THRESHOLD)
  {
    drive(TURN_DUTY_CYCLE, TURN_DUTY_CYCLE - (Kp * (right_reading - RIGHT_TAPE_THRESHOLD)));
    prev_state = 1;
  }

  // Left is on tape right is not, need to turn left
  else if(left_reading > LEFT_TAPE_THRESHOLD && right_reading < RIGHT_TAPE_THRESHOLD)
  {
    drive(TURN_DUTY_CYCLE - (Kp * (left_reading - LEFT_TAPE_THRESHOLD)), TURN_DUTY_CYCLE);
    prev_state = 2;
  }

  // Both are on the tape, turn both motors on
  else if(right_reading >= RIGHT_TAPE_THRESHOLD && left_reading >= LEFT_TAPE_THRESHOLD)
  {
    drive(ON_DUTY_CYCLE, ON_DUTY_CYCLE);
    prev_state = 0;
  }

  // Neither are on the tape
  else if(right_reading <= RIGHT_TAPE_THRESHOLD && left_reading <= LEFT_TAPE_THRESHOLD)
  {
    if(prev_state == 0) {
      drive(ON_DUTY_CYCLE, ON_DUTY_CYCLE);
    }
    if(prev_state == 1) {
      //Turn right
      drive(TURN_DUTY_CYCLE + 10, 0);
    }
    if(prev_state == 2) {
      //Turn left
      drive(0, TURN_DUTY_CYCLE + 10);
    }
  }
}
<<<<<<< HEAD
>>>>>>> 7f767f4 (Update main.cpp)
=======

void drive(int speedL, int speedR) {
        digitalWrite(Relay1, 0);
        digitalWrite(Relay2, 0);
        digitalWrite(Relay3, 0);

        if(speedL > 100) speedL = 100;
        if(speedL < -100) speedL = -100;
        if(speedR > 100) speedR = 100;
        if(speedR < -100) speedR = -100;

        if (speedL >= 0) {
                pwm_start(MOTOR_PWM_OUTPUT_LEFT_BACKWARDS, MOTOR_PWM_FREQUENCY_HZ, 0,
                        TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
                pwm_start(MOTOR_PWM_OUTPUT_LEFT, MOTOR_PWM_FREQUENCY_HZ, speedL,
                        TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
        }
        else {
                pwm_start(MOTOR_PWM_OUTPUT_LEFT, MOTOR_PWM_FREQUENCY_HZ, 0,
                        TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
                pwm_start(MOTOR_PWM_OUTPUT_LEFT_BACKWARDS, MOTOR_PWM_FREQUENCY_HZ, -speedL,
                        TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
        }
        if (speedR >= 0) {
                pwm_start(MOTOR_PWM_OUTPUT_RIGHT_BACKWARDS, MOTOR_PWM_FREQUENCY_HZ, 0,
                        TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
                pwm_start(MOTOR_PWM_OUTPUT_RIGHT, MOTOR_PWM_FREQUENCY_HZ, speedR,
                        TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
        }
        else {
                pwm_start(MOTOR_PWM_OUTPUT_RIGHT, MOTOR_PWM_FREQUENCY_HZ, 0,
                        TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
                pwm_start(MOTOR_PWM_OUTPUT_RIGHT_BACKWARDS, MOTOR_PWM_FREQUENCY_HZ, -speedR,
                        TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
        }
  }
>>>>>>> 8e64072 (Update Tapetracking with untested proportional control)
=======
  // put your main code here, to run repeatedly:
}
>>>>>>> b496ada (Organized Code)
