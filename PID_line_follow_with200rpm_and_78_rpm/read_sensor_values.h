#ifndef READ_SENSOR_VALUES_H
#define READ_SENSOR_VALUES_H
#include <Arduino.h>
#include "pins.h"
#include "variables.h"
#include "calibrate_sensor.h"
#include "oled_display.h"

extern int expectedValues[][numSensors];
extern int errorValues[];
extern bool conditionMet;
extern int defaultErrorValue;

void read_sensor_values();

#endif