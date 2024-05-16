#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include "pins.h"
#include "motor_drive.h"
#include "variables.h"
#include <util/atomic.h> // For the ATOMIC_BLOCK macro

extern int motor_pos;
extern long motor_prevT;
extern float motor_eprev;
extern float motor_eintegral;
extern float motor_kp;
extern float motor_kd;
extern float motor_ki;
extern int rpe;
extern float target_approx;

void count_encoder(float rpe_count);
void readEncoder();
void setMotor(int dir, int pwmVal, int pwm1, int pwm2, int in1, int in2, int in3, int in4);

#endif
