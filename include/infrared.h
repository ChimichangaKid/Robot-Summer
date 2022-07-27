//////////////////////////////////////////////////
//                                              //
// Functions and Defines Related to IR Readings //
//                                              //
//////////////////////////////////////////////////

#ifndef NUMBER_OF_IR_READINGS
#define NUMBER_OF_IR_READINGS 150
#endif

#ifndef IR_K_PROPORTIONAL
#define IR_K_PROPORTIONAL 0.001
#endif

#ifndef IR_K_DERIVATIVE
#define IR_K_DERIVATIVE 0
#endif

/**
 * Gets the difference between the left and right readings of the IR sensor
 * 
 * @param frequencykHz The desired frequency to filter for
 * @return The difference between the right reading and the left reading of the frequency.
 *         Return a positive integer if right is larger, negative if left is stronger.
 */
float getDifferenceInIRREadings(short frequency_khz);


/**
 * Calculates the PWM duty cycle to send to the motors for the infrared reading.
 * 
 * @param error The difference in the left and the right reading.
 */
float infraredPIDControl(float error);
