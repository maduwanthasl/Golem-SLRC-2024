#include "calculate_pid.h"

void calculate_pid()
{
  if (error <100){
    P = error;
    I = I + previous_I;
    D = error - previous_error;

    PID_value = (Kp * P) + (Ki * I) + (Kd * D);

    previous_I = I;
    previous_error = error;
  }
  else{
    PID_value = 0;
  }
}