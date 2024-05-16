#ifndef FUNCTIONS_H
#define FUNCTIONS_H
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
#include "line_follow.h"

void junction_1();
void junction_2();
void junction_3();
void junction_4();
void junction_5();
void junction_6_right();
void junction_6_left();

#endif