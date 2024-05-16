#include "variables.h"

// Define and initialize arrays
int sensorValues[numSensors]; // Array to store sensor values
int minValues[numSensors];    // Array to store minimum sensor values
int maxValues[numSensors];    // Array to store maximum sensor values
int threshold[numSensors];    // Array to store sensor thresholds

//Initial Speed of Motor
int initial_motor_speed = 75;

// PID Constants
float Kp = 4; //18
float Ki = 1; //6
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


