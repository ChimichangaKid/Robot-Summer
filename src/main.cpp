#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

//////////////////////////////////////
// Defines
//////////////////////////////////////

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display_handler(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// IR defines
#define IR_INPUT_PIN_LEFT PB0 // IR Pins
#define IR_INPUT_PIN_RIGHT PA7
#define NUMBER_OF_READINGS 150

// Motor Defines
#define MOTOR_PWM_OUTPUT_LEFT PA_8 // Motor Drive PWM Pins
#define MOTOR_PWM_OUTPUT_LEFT_BACKWARDS PA_9
#define MOTOR_PWM_OUTPUT_RIGHT PB_8
#define MOTOR_PWM_OUTPUT_RIGHT_BACKWARDS PB_9
#define MOTOR_PWM_FREQUENCY_HZ 100
#define ON_DUTY_CYCLE_PERCENT 20
#define OFF_DUTY_CYCLE 0

// PID Defines
#define KPROPORTIONAL 0.0006
#define KDERIVATIVE 0

// Other Defines
#define TEN_K_WAVE 10
#define ONE_K_WAVE 1
#define BACKWARDS_CONSTANT 0.1
#define DESIRED_ERROR 0

//////////////////////////////////////
// Function Declaration
//////////////////////////////////////

float GetDifferenceInReading(short frequencykHz);

//////////////////////////////////////
// Variable Setup
//////////////////////////////////////

// IR variable setup
short desired_wave = ONE_K_WAVE;
bool isTurned = false;
float start_timer;
float end_timer;
float start_time;
float end_time;
float Waveform_left[NUMBER_OF_READINGS];
float Waveform_right[NUMBER_OF_READINGS];
float compared_wave_left[NUMBER_OF_READINGS * 2];
float compared_wave_right[NUMBER_OF_READINGS * 2];
float convoluted_values_left[NUMBER_OF_READINGS];
float convoluted_values_right[NUMBER_OF_READINGS];
float deltaTLeft;
float deltaTRight;

// PID Variable Setup
float error;
float last_error = 0;
float proportional;
float derivative;
float adjustment;
float abs_error;

//////////////////////////////////////
// Setup
//////////////////////////////////////

/**
 * Gets the difference between the left and right readings of the IR sensor
 * 
 * @param frequencykHz The desired frequency to filter for
 * @return The difference between the right reading and the left reading of the frequency.
 *         Return a positive integer if right is larger, negative if left is stronger.
 */
float GetDifferenceInReading(short frequencykHz){

  start_time = micros();
  // Reads NUMBER_OF_READINGS values from the input pin, recentres wave about 0 and converts to voltage
  for(int reading_counter = 0; reading_counter < NUMBER_OF_READINGS; reading_counter++)
  {
    Waveform_left[reading_counter] = analogRead(IR_INPUT_PIN_LEFT) -1.866;
  }
  end_time = micros();

  // Determines time elapsed for readings
  deltaTLeft = (end_time - start_time) / NUMBER_OF_READINGS;

  start_time = micros();
  // Reads NUMBER_OF_READINGS values from the input pin, recentres wave about 0 and converts to voltage
  for(int reading_counter = 0; reading_counter < NUMBER_OF_READINGS; reading_counter++)
  {
    Waveform_right[reading_counter] = analogRead(IR_INPUT_PIN_RIGHT) -1.866;
  }
  end_time = micros();

  deltaTRight = (end_time - start_time) / NUMBER_OF_READINGS;

  // Generate the expected wave
  for(short int wave_creator = 0; wave_creator < 2 * NUMBER_OF_READINGS; wave_creator++)
  {
    compared_wave_left[wave_creator] = sin((wave_creator * frequencykHz * TWO_PI) * deltaTLeft / 1000);
    compared_wave_right[wave_creator] = sin((wave_creator * frequencykHz * TWO_PI) * deltaTRight / 1000);
  }

  // Cross correlate the values of the expected wave with the measured wave
  for(short int correlator = 0; correlator < NUMBER_OF_READINGS; correlator++)
  {
    convoluted_values_left[correlator] = 0;
    convoluted_values_right[correlator] = 0;

    for(short int k = 0; k < NUMBER_OF_READINGS; k++)
    {
      convoluted_values_left[correlator] += Waveform_left[k] * compared_wave_left[correlator + k];
      convoluted_values_right[correlator] += Waveform_right[k] * compared_wave_right[correlator + k];
    }
  }

  float max_value_left = 0;
  float max_value_right = 0;

  // Determine the maximum amplitude of the waves
  for(short int iterator = 0; iterator < NUMBER_OF_READINGS; iterator++)
  {
    if(convoluted_values_left[iterator] > max_value_left)
    { max_value_left = convoluted_values_left[iterator]; }
    if(convoluted_values_right[iterator] > max_value_right)
    { max_value_right = convoluted_values_right[iterator]; }
  }

  display_handler.clearDisplay();
  display_handler.setCursor(0, 25);
  display_handler.print(max_value_left, DEC);
  display_handler.setCursor(0, 50);
  display_handler.print(max_value_right, DEC);
  display_handler.display();

  return max_value_right - max_value_left;
}

void setup() {
  // Setup Input IR pins
  pinMode(IR_INPUT_PIN_LEFT, INPUT);
  pinMode(IR_INPUT_PIN_RIGHT, INPUT);

  // Setup output pwm motor pins
  pinMode(MOTOR_PWM_OUTPUT_LEFT, OUTPUT);
  pinMode(MOTOR_PWM_OUTPUT_RIGHT, OUTPUT);
  pinMode(MOTOR_PWM_OUTPUT_LEFT_BACKWARDS, OUTPUT);
  pinMode(MOTOR_PWM_OUTPUT_RIGHT_BACKWARDS, OUTPUT);

  // Initializes Display
  display_handler.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display_handler.display();

  display_handler.clearDisplay();
  display_handler.setTextSize(1);
  display_handler.setTextColor(SSD1306_WHITE);
  display_handler.setCursor(0,0);
  display_handler.println("Hello world!");
  display_handler.display();
  start_timer = millis();
}

//////////////////////////////////////
// Loop
//////////////////////////////////////

void loop() {
  end_timer = millis();
  error = GetDifferenceInReading(desired_wave);
  if(end_timer - start_timer > 3000 && !isTurned){
    desired_wave = TEN_K_WAVE;
    isTurned = true;
    do
    {
      pwm_start(MOTOR_PWM_OUTPUT_LEFT, MOTOR_PWM_FREQUENCY_HZ, OFF_DUTY_CYCLE, 
      TimerCompareFormat_t:: PERCENT_COMPARE_FORMAT);
      pwm_start(MOTOR_PWM_OUTPUT_RIGHT, MOTOR_PWM_FREQUENCY_HZ, OFF_DUTY_CYCLE, 
      TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
      pwm_start(MOTOR_PWM_OUTPUT_LEFT_BACKWARDS, MOTOR_PWM_FREQUENCY_HZ, OFF_DUTY_CYCLE, 
      TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
      pwm_start(MOTOR_PWM_OUTPUT_RIGHT_BACKWARDS, MOTOR_PWM_FREQUENCY_HZ, 15,
      TimerCompareFormat_t:: PERCENT_COMPARE_FORMAT);
      
      error = GetDifferenceInReading(desired_wave);
    } while (abs(error) < 20000);
    
  }
  abs_error = abs(error);

  if(abs_error < 1000){
    abs_error = 0;
  } else if (abs_error < 5000){
    abs_error = 5000;
  } else if(abs_error < 10000){
    abs_error = 10000;
  } else {
    abs_error = 10000;
  }
  proportional = KPROPORTIONAL * abs_error;
  derivative = KDERIVATIVE * (abs_error - last_error);
  adjustment = proportional + derivative;

  if (5000 > error && error > -5000){
    // Turn off other motors
    pwm_start(MOTOR_PWM_OUTPUT_LEFT, MOTOR_PWM_FREQUENCY_HZ, ON_DUTY_CYCLE_PERCENT, 
    TimerCompareFormat_t:: PERCENT_COMPARE_FORMAT);
    pwm_start(MOTOR_PWM_OUTPUT_RIGHT_BACKWARDS, MOTOR_PWM_FREQUENCY_HZ, OFF_DUTY_CYCLE,
    TimerCompareFormat_t:: PERCENT_COMPARE_FORMAT);

    // Start turning
    pwm_start(MOTOR_PWM_OUTPUT_RIGHT, MOTOR_PWM_FREQUENCY_HZ, ON_DUTY_CYCLE_PERCENT, 
    TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
    pwm_start(MOTOR_PWM_OUTPUT_LEFT_BACKWARDS, MOTOR_PWM_FREQUENCY_HZ, OFF_DUTY_CYCLE, 
    TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
  }

  // RIGHT READING BIGGER THAN LEFT, NEED TO TURN RIGHT
  else if (DESIRED_ERROR < error){
    // Turn right
    pwm_start(MOTOR_PWM_OUTPUT_RIGHT, MOTOR_PWM_FREQUENCY_HZ, ON_DUTY_CYCLE_PERCENT - adjustment, 
    TimerCompareFormat_t:: PERCENT_COMPARE_FORMAT);
    pwm_start(MOTOR_PWM_OUTPUT_LEFT_BACKWARDS, MOTOR_PWM_FREQUENCY_HZ, OFF_DUTY_CYCLE,
    TimerCompareFormat_t:: PERCENT_COMPARE_FORMAT);
    pwm_start(MOTOR_PWM_OUTPUT_LEFT, MOTOR_PWM_FREQUENCY_HZ, ON_DUTY_CYCLE_PERCENT + adjustment, 
    TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
    pwm_start(MOTOR_PWM_OUTPUT_RIGHT_BACKWARDS, MOTOR_PWM_FREQUENCY_HZ, OFF_DUTY_CYCLE, 
    TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
  }

  else if (DESIRED_ERROR > error){
    // Turn right
    pwm_start(MOTOR_PWM_OUTPUT_RIGHT, MOTOR_PWM_FREQUENCY_HZ, ON_DUTY_CYCLE_PERCENT + adjustment, 
    TimerCompareFormat_t:: PERCENT_COMPARE_FORMAT);
    pwm_start(MOTOR_PWM_OUTPUT_LEFT_BACKWARDS, MOTOR_PWM_FREQUENCY_HZ, OFF_DUTY_CYCLE,
    TimerCompareFormat_t:: PERCENT_COMPARE_FORMAT);
    pwm_start(MOTOR_PWM_OUTPUT_LEFT, MOTOR_PWM_FREQUENCY_HZ, ON_DUTY_CYCLE_PERCENT - adjustment, 
    TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
    pwm_start(MOTOR_PWM_OUTPUT_RIGHT_BACKWARDS, MOTOR_PWM_FREQUENCY_HZ, OFF_DUTY_CYCLE, 
    TimerCompareFormat_t::PERCENT_COMPARE_FORMAT);
  }

  

  display_handler.clearDisplay();
  display_handler.setCursor(0, 0);
  display_handler.print(error, DEC);
  display_handler.display();
  last_error = abs_error;
}