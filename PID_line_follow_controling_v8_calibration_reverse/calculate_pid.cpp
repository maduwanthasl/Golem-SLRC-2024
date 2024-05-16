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

void calculate_pid_reverse(){
  if (reverse_error <100){
    P = reverse_error;
    I = I + previous_I;
    D = reverse_error - previous_error;

    PID_value = (Kp * P) + (Ki * I) + (Kd * D);

    previous_I = I;
    previous_error = reverse_error;
  }
  else{
    PID_value = 0;
  }

}