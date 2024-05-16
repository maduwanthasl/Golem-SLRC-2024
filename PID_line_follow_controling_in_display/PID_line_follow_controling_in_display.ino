#include "pins.h"
#include "variables.h"
#include "motor_drive.h"
#include "calculate_pid.h"
#include "read_sensor_values.h"
#include "calibrate_sensor.h"
#include "motor_pwm_control.h"
#include "line_follow.h"
#include "oled_display.h"
#include "count_encoder.h"

void setup()
{
  pinMode(leftForward, OUTPUT);
  pinMode(leftBackward, OUTPUT);
  pinMode(rightForward, OUTPUT);
  pinMode(rightBackward, OUTPUT);
  pinMode(leftmotor_pwm, OUTPUT); // Changed from ENA
  pinMode(rightmotor_pwm, OUTPUT); // Changed from ENB
  pinMode(ENCA, INPUT);
  pinMode(ENCB, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA), readEncoder, RISING);

  setupDisplay();
  

  Serial.begin(9600);                     //setting serial monitor at a default baund rate of 9600
  Serial.println("Started !!");
  delay(1000);
}

void loop(){
  loopDisplay();
  // read_sensor_values();


}






