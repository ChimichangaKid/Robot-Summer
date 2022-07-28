#include <Arduino.h>

void setup() {
  // put your setup code here, to run once:
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

  // Neither are on the tape, turn off
  else if(right_reading >= RIGHT_TAPE_THRESHOLD && left_reading >= LEFT_TAPE_THRESHOLD)
  {
    if(prev_state == 0) {
      drive(ON_DUTY_CYCLE, ON_DUTY_CYCLE);
    }
    if(prev_state == 1) {
      //Turn right
      drive(TURN_DUTY_CYCLE, 0);
    }
    if(prev_state == 2) {
      //Turn left
      drive(0, TURN_DUTY_CYCLE);
    }
  }
}
<<<<<<< HEAD
>>>>>>> 7f767f4 (Update main.cpp)
=======

void drive(int speedL, int speedR) {
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
