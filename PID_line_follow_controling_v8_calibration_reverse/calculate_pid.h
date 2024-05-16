#ifndef CALCULATE_PID_H
#define CALCULATE_PID_H
#include <Arduino.h>
#include "pins.h"
#include "variables.h"
#include "read_sensor_values.h"

void calculate_pid();
void calculate_pid_reverse();

#endif