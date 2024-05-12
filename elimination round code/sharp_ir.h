#ifndef SHARP_IR_H
#define SHARP_IR_H

#include <Arduino.h>
#include <NewPing.h>
#include "pins.h"

// Constants for the Sharp IR sensor
extern const int sensorPin[]; // Pin connected to the sensor
extern const int AVERAGE_OF; // Number of readings to average
extern const int MAX_READINGS; // Maximum number of readings to store
extern float distance[]; // Array to store distance readings
extern float Variance[]; // Array to store distance readings
extern int numReadings; // Number of readings taken
extern const float MCU_VOLTAGE; // Voltage supplied to the microcontroller
extern int currentSize; 


void readDistance(int sensor);
float calculateStatistics();
void appendToVariance(float newValue);
void sharp_ir_loop();
void sharp_ir_ultra_loop();


#endif