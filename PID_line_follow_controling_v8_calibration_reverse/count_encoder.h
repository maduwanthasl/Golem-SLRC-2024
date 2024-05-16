#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include "pins.h"
#include "motor_drive.h"
#include "variables.h"
#include <util/atomic.h> // For the ATOMIC_BLOCK macro
#include "read_sensor_values.h"

extern int motor_pos;
extern int motor_pos2;
extern long motor_prevT;
extern float motor_eprev;
extern float motor_eintegral;
extern float motor_eintegral2;
extern float motor_kp;
extern float motor_kd;
extern float motor_ki;
extern int rpe;
extern float target_approx;

void count_encoder(float rpe_count);
void readEncoder();
void readEncoder2();
void error_calculate(int motor_pos, float rpe_count);
void error_calculate2(int motor_pos2, float rpe_count);
void setMotor(int dir, int pwmVal, int pwm, int in1, int in2);
// void sharp_turns(int a);

#endif
