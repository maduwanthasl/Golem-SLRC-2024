#ifndef MOTOR_DRIVE_H
#define MOTOR_DRIVE_H
#include <Arduino.h>
#include "pins.h"


void forward();
void reverse();
void left();
void right();
void sharpLeftTurn();
void sharpRightTurn();
void U_turn();
void Brake_fast();
void stop_bot();




#endif