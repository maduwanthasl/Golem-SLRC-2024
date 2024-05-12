#ifndef MOTOR_PWM_CONTROL_H
#define MOTOR_PWM_CONTROL_H
#include <Arduino.h>
#include "pins.h"
#include "variables.h"
#include "calculate_pid.h"
#include "motor_drive.h"

void motor_control();
void motor_control_reverse();

#endif