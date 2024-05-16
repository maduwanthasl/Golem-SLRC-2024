#ifndef SERVO_H
#define SERVO_H

#include <Arduino.h>
#include <Servo.h>

extern int pos;    // variable to store the servo position

void servo_setup();
void mg995_down();
void mg995_up();
void mg90_close();
void mg90_open();
void mg995_down_2();
void mg995_up_2();


#endif