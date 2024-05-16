#ifndef LINE_FOLLOW_H
#define LINE_FOLLOW_H
#include <Arduino.h>
#include "pins.h"
#include "variables.h"
#include "read_sensor_values.h"
#include "motor_drive.h"
#include "calculate_pid.h"
#include "motor_pwm_control.h"
#include "color_sensor.h"
#include "tca9548a.h"
#include "sharp_ir.h"
#include "servo.h"
#include "functions.h"

void followPath();

#endif