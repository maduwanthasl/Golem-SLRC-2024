#ifndef VARIABLES_H
#define VARIABLES_H
#include <Arduino.h>
#include "pins.h"

extern int sensorValues[numSensors]; // Array to store sensor values
extern int minValues[numSensors]; // Array to store minimum sensor values
extern int maxValues[numSensors]; // Array to store maximum sensor values
extern int threshold[numSensors]; // Array to store sensor thresholds   
extern int reverseMinValues[numReverseSensors];
extern int reverseMaxValues[numReverseSensors];
extern int reverseThreshold[numReverseSensors];
extern int reverseSensorPins[numReverseSensors];


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

//Junction count
extern int rpe;
extern float rpe_count;
extern float target_approx;

//color sensor
extern String dominantColor;
extern String dominant_front_color;
extern String dominant_down_left_color;
extern String dominant_down_right_color;
extern String color;

//tof sensor
extern int distance_tof; // Variable to store the distance measurement

//tca9845a sensor
extern int tof_front;
extern int color_front;
extern int color_down_left;
extern int color_down_right;
extern int gyro;
extern float degree;

extern float gyroDegree;





#endif
