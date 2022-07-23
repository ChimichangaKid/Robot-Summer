#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display_handler(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define TAPE_INPUT_PIN_LEFT PA4 // Tape Tracking Pins
#define TAPE_INPUT_PIN_RIGHT PA5

#define LEFT_TAPE_THRESHOLD 700
#define RIGHT_TAPE_THRESHOLD 710

#define MOTOR_PWM_OUTPUT_LEFT PA_8 // Motor Drive PWM Pins
#define MOTOR_PWM_OUTPUT_LEFT_BACKWARDS PA_9
#define MOTOR_PWM_OUTPUT_RIGHT PB_8
#define MOTOR_PWM_OUTPUT_RIGHT_BACKWARDS PB_9

#define MOTOR_PWM_FREQUENCY_HZ 100
#define ON_DUTY_CYCLE_PERCENT 30
#define OFF_DUTY_CYCLE 0
#define TURN_DUTY_CYCLE 20
#define Kp 0.05

// Digital Read Readings
volatile uint16_t left_reading;
volatile uint16_t right_reading;

volatile u_int8_t prev_state = 0;

// Variable to show program is running
uint16_t counter = 0;

void setup() {
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
}

void loop() {
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
    pwm_start(MOTOR_PWM_OUTPUT_LEFT_BACKWARDS, MOTOR_PWM_FREQUENCY_HZ, OFF_DUTY_CYCLE,
              TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
    pwm_start(MOTOR_PWM_OUTPUT_RIGHT, MOTOR_PWM_FREQUENCY_HZ, OFF_DUTY_CYCLE,
              TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
    pwm_start(MOTOR_PWM_OUTPUT_RIGHT_BACKWARDS, MOTOR_PWM_FREQUENCY_HZ, OFF_DUTY_CYCLE,
              TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
    pwm_start(MOTOR_PWM_OUTPUT_LEFT, MOTOR_PWM_FREQUENCY_HZ, TURN_DUTY_CYCLE,
              TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
    prev_state = 1;
  }

  // Left is on tape right is not, need to turn left
  else if(left_reading > LEFT_TAPE_THRESHOLD && right_reading < RIGHT_TAPE_THRESHOLD)
  {
    pwm_start(MOTOR_PWM_OUTPUT_RIGHT_BACKWARDS, MOTOR_PWM_FREQUENCY_HZ, OFF_DUTY_CYCLE,
              TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
    pwm_start(MOTOR_PWM_OUTPUT_LEFT, MOTOR_PWM_FREQUENCY_HZ, OFF_DUTY_CYCLE,
              TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
    pwm_start(MOTOR_PWM_OUTPUT_LEFT_BACKWARDS, MOTOR_PWM_FREQUENCY_HZ, OFF_DUTY_CYCLE,
              TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
    pwm_start(MOTOR_PWM_OUTPUT_RIGHT, MOTOR_PWM_FREQUENCY_HZ, TURN_DUTY_CYCLE,
              TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
    prev_state = 2;
  }

  // Both are on the tape, turn both motors on
  else if(right_reading >= RIGHT_TAPE_THRESHOLD && left_reading >= LEFT_TAPE_THRESHOLD)
  {
    pwm_start(MOTOR_PWM_OUTPUT_RIGHT_BACKWARDS, MOTOR_PWM_FREQUENCY_HZ, OFF_DUTY_CYCLE,
              TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
    pwm_start(MOTOR_PWM_OUTPUT_LEFT_BACKWARDS, MOTOR_PWM_FREQUENCY_HZ, OFF_DUTY_CYCLE,
              TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
    pwm_start(MOTOR_PWM_OUTPUT_LEFT, MOTOR_PWM_FREQUENCY_HZ, ON_DUTY_CYCLE_PERCENT,
              TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
    pwm_start(MOTOR_PWM_OUTPUT_RIGHT, MOTOR_PWM_FREQUENCY_HZ, ON_DUTY_CYCLE_PERCENT,
              TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
    prev_state = 0;
  }

  // Neither are on the tape, turn off
  else if(right_reading >= RIGHT_TAPE_THRESHOLD && left_reading >= LEFT_TAPE_THRESHOLD)
  {
    if(prev_state == 0) {
      pwm_start(MOTOR_PWM_OUTPUT_RIGHT_BACKWARDS, MOTOR_PWM_FREQUENCY_HZ, OFF_DUTY_CYCLE,
              TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
      pwm_start(MOTOR_PWM_OUTPUT_LEFT_BACKWARDS, MOTOR_PWM_FREQUENCY_HZ, OFF_DUTY_CYCLE,
              TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
      pwm_start(MOTOR_PWM_OUTPUT_LEFT, MOTOR_PWM_FREQUENCY_HZ, ON_DUTY_CYCLE_PERCENT,
              TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
      pwm_start(MOTOR_PWM_OUTPUT_RIGHT, MOTOR_PWM_FREQUENCY_HZ, ON_DUTY_CYCLE_PERCENT,
              TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
    }
    if(prev_state == 1) {
      //Turn right
      pwm_start(MOTOR_PWM_OUTPUT_LEFT_BACKWARDS, MOTOR_PWM_FREQUENCY_HZ, OFF_DUTY_CYCLE,
              TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
      pwm_start(MOTOR_PWM_OUTPUT_RIGHT, MOTOR_PWM_FREQUENCY_HZ, OFF_DUTY_CYCLE,
              TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
      pwm_start(MOTOR_PWM_OUTPUT_RIGHT_BACKWARDS, MOTOR_PWM_FREQUENCY_HZ, OFF_DUTY_CYCLE,
              TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
      pwm_start(MOTOR_PWM_OUTPUT_LEFT, MOTOR_PWM_FREQUENCY_HZ, TURN_DUTY_CYCLE,
              TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
    }
    if(prev_state == 2) {
      //Turn left
      pwm_start(MOTOR_PWM_OUTPUT_RIGHT_BACKWARDS, MOTOR_PWM_FREQUENCY_HZ, OFF_DUTY_CYCLE,
              TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
              pwm_start(MOTOR_PWM_OUTPUT_LEFT, MOTOR_PWM_FREQUENCY_HZ, OFF_DUTY_CYCLE,
              TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
      pwm_start(MOTOR_PWM_OUTPUT_LEFT_BACKWARDS, MOTOR_PWM_FREQUENCY_HZ, OFF_DUTY_CYCLE,
              TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
      pwm_start(MOTOR_PWM_OUTPUT_RIGHT, MOTOR_PWM_FREQUENCY_HZ, TURN_DUTY_CYCLE,
              TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
    }
  }

}
>>>>>>> 7f767f4 (Update main.cpp)
