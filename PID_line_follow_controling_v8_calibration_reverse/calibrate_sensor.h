#ifndef CALIBRATE_SENSOR_H
#define CALIBRATE_SENSOR_H
#include <Arduino.h>
#include <EEPROM.h> // Include the EEPROM library
#include "pins.h"
#include "variables.h"
#include "motor_drive.h"
#include "read_sensor_values.h"
#include "reverse_ir.h"

void saveThresholdToEEPROM();
void readThresholdFromEEPROM();
void calibrateSensors();

void saveThresholdToEEPROMreverse();
void readThresholdFromEEPROMreverse();
void calibrateReverseSensors();

#endif