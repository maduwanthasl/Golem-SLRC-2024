#include "count_encoder.h"

// Define the variables with static keyword to limit their scope to this translation unit
static int motor_pos;
static long motor_prevT = 0;
static float motor_eprev = 0;
static float motor_eintegral = 0;
static float motor_kp = 1;
static float motor_kd = 0.025;
static float motor_ki = 0.0;

// If you want to provide accessors to these variables, you can define them here as well.


void count_encoder(float rpe_count )
{
  motor_pos = 0;
  do{
  float target_approx = rpe * rpe_count - 5;
  if (motor_pos >= target_approx && target_approx > 0)
  {
    // Stop the motors
    setMotor(0, 0, leftmotor_pwm, rightmotor_pwm, leftBackward, leftForward, rightBackward, rightForward);
    // Break the loop
    return ;
  }
  if (motor_pos < target_approx && target_approx < 0)
  {
    // Stop the motors
    setMotor(0, 0, leftmotor_pwm, rightmotor_pwm, leftBackward, leftForward, rightBackward, rightForward);
    // Break the loop
    return;
  }

  // time difference
  long currT = micros();
  float deltaT = ((float)(currT - motor_prevT)) / (1.0e6);
  motor_prevT = currT;

  // error
  int e = motor_pos - rpe * rpe_count;

  // derivative
  float dedt = (e - motor_eprev) / (deltaT);

  // integral
  motor_eintegral = motor_eintegral + e * deltaT;

  // control signal
  float u = motor_kp * e + motor_kd * dedt + motor_ki * motor_eintegral;

  // motor power
  float pwr = fabs(u);
  if (pwr > 75)
  {
    pwr = 75;
  }
  else if (pwr < 30)
  { // Add this condition to limit pwr above 30
    pwr = 30;
  }

  // motor direction
  int dir = 1;
  if (u < 0)
  {
    dir = -1;
  }

  // signal the motors
  setMotor(dir, pwr, leftmotor_pwm, rightmotor_pwm, leftBackward, leftForward, rightBackward, rightForward);

  // store previous error
  motor_eprev = e;
  Serial.println("1000");
  } while (!((motor_pos >= target_approx && target_approx > 0) || (motor_pos < target_approx && target_approx < 0)));
}

void setMotor(int dir, int pwmVal, int pwm, int pwm2, int in1, int in2, int in3, int in4)
{
  analogWrite(pwm, pwmVal);
  analogWrite(pwm2, pwmVal);
  if (dir == 1)
  {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  else if (dir == -1)
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
  else
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }
}

void readEncoder()
{
  int b = digitalRead(ENCB);
  if (b > 0)
  {
    motor_pos++;
  }
  else
  {
    motor_pos--;
  }
}
