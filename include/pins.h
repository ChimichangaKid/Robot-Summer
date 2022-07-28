#include <Arduino.h>

/* Driver Pin */
#define RIGHT_DRIVE_A PB_8
#define RIGHT_DRIVE_B PB_9
#define LEFT_DRIVE_A PA_8
#define LEFT_DRIVE_B PA_9

/* Relay Pins */
#define RELAY_CH1 PB12 // Left Arm
#define RELAY_CH2 PB13
#define RELAY_CH3 PB14 // Right Arm
// BOTH 13 & 14 for wall

/* IR PINS */
#define IR_INPUT_PIN_LEFT PB0 
#define IR_INPUT_PIN_RIGHT PA7 

/* TAPE TRACKING PINS */
#define TAPE_INPUT_PIN_LEFT PA4
#define TAPE_INPUT_PIN_RIGHT PA5

/* IDOL DETECTION PINS */
#define ECHO_PIN PB3
#define TRIGGER_PIN PB4