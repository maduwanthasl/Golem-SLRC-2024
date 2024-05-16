#include "motor_pwm_control.h"


void motor_control()
{
  // Calculating the effective motor speed:
  int left_motor_speed = initial_motor_speed + PID_value;
  int right_motor_speed = initial_motor_speed - PID_value;

  // The motor speed should not exceed the max PWM value
  left_motor_speed = constrain(left_motor_speed, 0, 255);
  right_motor_speed = constrain(right_motor_speed, 0, 255);

  // Serial.print(PID_value);
  // Serial.print("\t");
  
  // Serial.print(left_motor_speed);
  // Serial.print("\t");
  // Serial.println(right_motor_speed);
  // delay(1000);

  analogWrite(leftmotor_pwm, left_motor_speed); //Left Motor Speed
  analogWrite(rightmotor_pwm, right_motor_speed); //Right Motor Speed

  //following lines of code are to make the bot move forward
  forward();
}

