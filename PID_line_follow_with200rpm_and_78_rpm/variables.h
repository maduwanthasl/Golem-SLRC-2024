#ifndef VARIABLES_H
#define VARIABLES_H
#include <Arduino.h>
#include "pins.h"

extern int sensorValues[numSensors]; // Array to store sensor values
extern int minValues[numSensors]; // Array to store minimum sensor values
extern int maxValues[numSensors]; // Array to store maximum sensor values
extern int threshold[numSensors]; // Array to store sensor thresholds   


//Initial Speed of Motor
extern int initial_motor_speed;

// PID Constants
extern float Kp;
extern float Ki;
extern float Kd;

extern float error, P, I, D, PID_value;
extern float previous_error, previous_I;

extern int flag;

//Junction count
extern int junction_count;


#endif
