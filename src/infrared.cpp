//////////////////////////////////////////
//                                      //
// Functions related to IR tracking     //
//                                      //
//////////////////////////////////////////
#include "./../include/infrared.h"   
#include "./../include/pins.h"
#include <Arduino.h>

#define IR_DRIVE_SPEED 30

#define DESIRED_IR_ERROR 0

//////////////////////////////////////////
// Variable Setup
//////////////////////////////////////////

float Waveform_left[NUMBER_OF_IR_READINGS];
float Waveform_right[NUMBER_OF_IR_READINGS];
float compared_wave_left[NUMBER_OF_IR_READINGS * 2];
float compared_wave_right[NUMBER_OF_IR_READINGS * 2];
float convoluted_values_left[NUMBER_OF_IR_READINGS];
float convoluted_values_right[NUMBER_OF_IR_READINGS];

float proportional;
float derivative;
float last_error = 0;

/**
 * Gets the difference between the left and right readings of the IR sensor
 * 
 * @param frequencykHz The desired frequency to filter for
 * @return The difference between the right reading and the left reading of the frequency.
 *         Return a positive integer if right is larger, negative if left is stronger.
 */
float getDifferenceInIRReadings(short frequency_khz){
    float start_time = micros();
    for(int reading_counter = 0; reading_counter < NUMBER_OF_IR_READINGS; reading_counter++)
    {
        Waveform_left[reading_counter] = analogRead(IR_INPUT_PIN_LEFT) -1.866;
    }
    float end_time = micros();

    float deltaTLeft = (end_time - start_time) / NUMBER_OF_IR_READINGS;
    start_time = micros();
        // Reads NUMBER_OF_READINGS values from the input pin, recentres wave about 0 and converts to voltage
    for(int reading_counter = 0; reading_counter < NUMBER_OF_IR_READINGS; reading_counter++)
    {
        Waveform_right[reading_counter] = analogRead(IR_INPUT_PIN_RIGHT) -1.866;
    }
    end_time = micros();

    float deltaTRight = (end_time - start_time) / NUMBER_OF_IR_READINGS;

    // Generate the expected wave
    for(short int wave_creator = 0; wave_creator < 2 * NUMBER_OF_IR_READINGS; wave_creator++)
    {
        compared_wave_left[wave_creator] = sin((wave_creator * frequency_khz * TWO_PI) * deltaTLeft / 1000);
        compared_wave_right[wave_creator] = sin((wave_creator * frequency_khz * TWO_PI) * deltaTRight / 1000);
    }

    // Cross correlate the values of the expected wave with the measured wave
    for(short int correlator = 0; correlator < NUMBER_OF_IR_READINGS; correlator++)
    {
        convoluted_values_left[correlator] = 0;
        convoluted_values_right[correlator] = 0;

        for(short int k = 0; k < NUMBER_OF_IR_READINGS; k++)
        {
            convoluted_values_left[correlator] += Waveform_left[k] * compared_wave_left[correlator + k];
            convoluted_values_right[correlator] += Waveform_right[k] * compared_wave_right[correlator + k];
        }
    }

    float max_value_left = 0;
    float max_value_right = 0;
    // Determine the maximum amplitude of the waves
    for(short int iterator = 0; iterator < NUMBER_OF_IR_READINGS; iterator++)
    {
        if(convoluted_values_left[iterator] > max_value_left)
        { max_value_left = convoluted_values_left[iterator]; }
        if(convoluted_values_right[iterator] > max_value_right)
        { max_value_right = convoluted_values_right[iterator]; }
    }

    return max_value_right - max_value_left;
}

/**
 * Calculates the PWM duty cycle to send to the motors for the infrared reading.
 * 
 * @param error The difference in the left and the right reading.
 */
float infraredPIDControl(float error){
    proportional = IR_K_PROPORTIONAL * error;
    derivative = IR_K_DERIVATIVE * (error - last_error);
    last_error = error;

    return proportional + derivative + IR_DRIVE_SPEED;
}