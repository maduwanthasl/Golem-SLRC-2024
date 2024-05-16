#ifndef READ_SENSOR_VALUES_H
#define READ_SENSOR_VALUES_H
#include <Arduino.h>
#include "pins.h"
#include "variables.h"
#include "calibrate_sensor.h"
#include "oled_display.h"
#include "count_encoder.h"
#include "reverse_ir.h"

extern int expectedValues[][numSensors];
extern int errorValues[];
extern bool conditionMet;
extern int defaultErrorValue;
extern int expectedValues_reverse[][numReverseSensors];
extern int reverse_errorValues[];

void read_sensor_values();
void read_sensor_values_reverse();

#endif