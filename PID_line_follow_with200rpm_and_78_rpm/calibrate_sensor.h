#ifndef CALIBRATE_SENSOR_H
#define CALIBRATE_SENSOR_H
#include <Arduino.h>
#include <EEPROM.h> // Include the EEPROM library
#include "pins.h"
#include "variables.h"
#include "motor_drive.h"

void saveThresholdToEEPROM();
void readThresholdFromEEPROM();
void calibrateSensors();

#endif