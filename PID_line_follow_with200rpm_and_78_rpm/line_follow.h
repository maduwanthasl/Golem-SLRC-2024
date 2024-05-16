#ifndef LINE_FOLLOW_H
#define LINE_FOLLOW_H
#include <Arduino.h>
#include "pins.h"
#include "variables.h"
#include "read_sensor_values.h"
#include "motor_drive.h"
#include "calculate_pid.h"
#include "motor_pwm_control.h"

void followPath();

#endif