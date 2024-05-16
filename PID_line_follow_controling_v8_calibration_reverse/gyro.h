#ifndef GYRO_H
#define GYRO_H

#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include "variables.h"
#include "motor_drive.h"
#include "read_sensor_values.h"

extern float gyroDegree;
extern float gyroCalibrationFactor;
extern bool isFirstLoopComplete;
extern float previousTime;


void gyro_setup();
float gyro_loop();
void sharp_turns(int a);

#endif
