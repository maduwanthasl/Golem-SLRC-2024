#include "count_encoder.h"

// Define the variables with static keyword to limit their scope to this translation unit
static int motor_pos = 0;
static int motor_pos2 = 0;
static long motor_prevT = 0;
static float motor_eprev = 0;
static float motor_eintegral = 0;
static float motor_eintegral2 = 0; 
static float motor_kp = 1;
static float motor_kd = 0.025;
static float motor_ki = 0;

// Define a flag to indicate whether both motors have reached the target position
bool motorsReachedTarget = false;

void count_encoder(float rpe_count)
{
  float target_approx = rpe * rpe_count - 5;
  
  // Loop until one of the conditions is met
  while (true) {
    // Check if both motors are within target range
    if ((motor_pos >= -target_approx && target_approx < 0 && motor_pos2 >= -target_approx && target_approx < 0) ||
        (motor_pos < -target_approx && target_approx > 0 && motor_pos2 < -target_approx && target_approx > 0)) {
      // Stop the motors
      setMotor(0, 0, leftmotor_pwm, leftBackward, leftForward);
      setMotor(0, 0, rightmotor_pwm, rightBackward, rightForward);
      return;
    }
    
    // Calculate errors and control motors
    error_calculate(abs(motor_pos), rpe_count);
    error_calculate2(abs(motor_pos2), rpe_count);
    
    // Print motor positions for debugging
    Serial.print("motor_pos: ");
    Serial.println(motor_pos);
    Serial.print("motor_pos2: ");
    Serial.println(motor_pos2);
    
    // Check if one motor is ahead of the other
    if (abs(motor_pos - motor_pos2) > 5) { // Adjust threshold as needed
      // Stop the faster motor
      setMotor(0, 0, (motor_pos > motor_pos2) ? leftmotor_pwm : rightmotor_pwm,
               (motor_pos > motor_pos2) ? leftBackward : leftForward,
               (motor_pos > motor_pos2) ? rightForward : rightBackward);
    }
    
    // Add a small delay to avoid tight loop without burdening the system
    delay(10);
  }
}


void error_calculate(int motor_pos, float rpe_count)
{
  // Calculate time difference
  long currT = micros();
  float deltaT = ((float)(currT - motor_prevT)) / (1.0e6);
  motor_prevT = currT;

  // Calculate error
  int e = motor_pos - rpe * rpe_count;

  // Calculate derivative
  float dedt = (e - motor_eprev) / deltaT;

  // Calculate integral
  motor_eintegral += e * deltaT;

  // Calculate control signal
  float u = motor_kp * e + motor_kd * dedt + motor_ki * motor_eintegral;

  // Limit control signal to ensure it's within acceptable range
  float pwr = constrain(fabs(u), 0, 255);

  // Determine direction
  int dir = (u >= 0) ? 1 : -1;

  // Set motor speed and direction
  setMotor(dir, pwr, leftmotor_pwm, leftBackward, leftForward);

  // Store previous error
  motor_eprev = e;
}

void error_calculate2(int motor_pos2, float rpe_count)
{
  // Calculate time difference
  long currT = micros();
  float deltaT = ((float)(currT - motor_prevT)) / (1.0e6);
  motor_prevT = currT;

  // Calculate error
  int e = motor_pos2 - rpe * rpe_count;

  // Calculate derivative
  float dedt = (e - motor_eprev) / deltaT;

  // Calculate integral
  motor_eintegral2 += e * deltaT;

  // Calculate control signal
  float u = motor_kp * e + motor_kd * dedt + motor_ki * motor_eintegral2;

  // Limit control signal to ensure it's within acceptable range
  float pwr = constrain(fabs(u), 0, 255);

  // Determine direction
  int dir = (u >= 0) ? 1 : -1;

  // Set motor speed and direction
  setMotor(dir, pwr, rightmotor_pwm, rightBackward, rightForward);

  // Store previous error
  motor_eprev = e;
}

void setMotor(int dir, int pwmVal, int pwm, int in1, int in2)
{
  // Set PWM value
  analogWrite(pwm, pwmVal);

  // Set motor direction
  digitalWrite(in1, (dir == 1) ? HIGH : LOW);
  digitalWrite(in2, (dir == -1) ? HIGH : LOW);
}

void readEncoder()
{
  // Update motor position based on encoder input
  int b = digitalRead(ENCB);
  motor_pos += (b > 0) ? 1 : -1;
}

void readEncoder2()
{
  // Update motor position based on encoder input
  int b = digitalRead(ENCD);
  motor_pos2 += (b > 0) ? -1 : 1;
}
