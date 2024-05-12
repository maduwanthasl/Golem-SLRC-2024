#include "variables.h"

// Define and initialize arrays
int sensorValues[numSensors]; // Array to store sensor values
int minValues[numSensors];    // Array to store minimum sensor values
int maxValues[numSensors];    // Array to store maximum sensor values
int threshold[numSensors];    // Array to store sensor thresholds
int reverseMinValues[numReverseSensors];
int reverseMaxValues[numReverseSensors];
int reverseThreshold[numReverseSensors];
int reverseSensorPins[numReverseSensors];

//Initial Speed of Motor
int initial_motor_speed = 150;

// PID Constants
float Kp = 14; //9
float Ki = 17; //8
float Kd = 0; //8

float error = 0, P = 0, I = 0, D = 0, PID_value = 0;
float previous_error = 0, previous_I = 0;

int flag = 0;

//Junction count
int junction_count = 0;

//Define encoder counting variables
int rpe = 2480;
float rpe_count;
float target_approx;

//color sensor
String dominantColor;
String dominant_front_color;
String dominant_down_left_color;
String dominant_down_right_color;
String color;



//tof sensor
int distance_tof; // Variable to store the distance measurement

//tca9845a
int tof_front = 0;
int color_front =5;
int color_down_left = 6;
int color_down_right = 7;
int gyro = 2;
float degree;

float gyroDegree;


