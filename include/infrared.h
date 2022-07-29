//////////////////////////////////////////////////
//                                              //
// Functions and Defines Related to IR Readings //
//                                              //
//////////////////////////////////////////////////

#ifndef INFRARED_H
#define INFRARED_H

#ifndef NUMBER_OF_IR_READINGS
#define NUMBER_OF_IR_READINGS 150
#endif

#ifndef IR_K_PROPORTIONAL
#define IR_K_PROPORTIONAL 0.001
#endif

#ifndef IR_K_DERIVATIVE
#define IR_K_DERIVATIVE 0
#endif

#ifndef ONE_KHZ
#define ONE_KHZ 1
#endif

#ifndef TEN_KHZ
#define TEN_KHZ 10
#endif

/**
 * Gets the difference between the left and right readings of the IR sensor
 * 
 * @param frequencykHz The desired frequency to filter for
 * @return The difference between the right reading and the left reading of the frequency.
 *         Return a positive integer if right is larger, negative if left is stronger.
 */
float getDifferenceInIRReadings(short);


/**
 * Calculates the PWM duty cycle to send to the motors for the infrared reading.
 * 
 * @param error The difference in the left and the right reading.
 */
float infraredPIDControl(float);

/**
 * Determines the drive direction and speed of the IR following
 * 
 * @param error The difference in the left and the right reading.
 * @param PID The PID calculation to adjust the speed of the driving.
 */
void infraredDrive(float error, float PID);

/**
 * Rotates the robot until it sees the desired frequency beacon.
 * 
 * @param frequency_khz The frequency that the robot is searching for
 */
void locateBeacon(short frequency_kHz);

#endif
