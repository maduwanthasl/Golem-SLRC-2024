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
#include "color_sensor.h"
#include <Arduino.h>
#include "Adafruit_VL53L0X.h"
#include "tca9548a.h"
#include "gyro.h"
#include "sharp_ir.h"
#include "servo.h"
#include "reverse_ir.h"


// ColorSensor colorSensor; // Create an instance of the ColorSensor class
// MeasureDistanceTOF distanceSensor; // Instantiate the MeasureDistanceTOF object


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
  pinMode(ENCC, INPUT);
  pinMode(ENCD, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA), readEncoder, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCC), readEncoder2, RISING);

  pinMode(a_blue, OUTPUT);
  pinMode(a_green, OUTPUT);
  pinMode(b_blue, OUTPUT);
  pinMode(b_green, OUTPUT);
  pinMode(b_red, OUTPUT); // Changed from ENA
  pinMode(metal_out, INPUT);


  Serial.begin(9600);                     //setting serial monitor at a default baund rate of 9600
  Serial.println("Started !!");
  delay(1000);

  // color sensor and tof setup
  tca9548a_setup();
  servo_setup();
  reverse_ir_setup();

}

void loop(){
  // read_sensor_values();
  TCA9548A_display(4);
  // reverse_ir_loop();


  // mg995_down();
  // delay(2000);
  // mg90_open();
  // mg995_up();
  // delay(5000);
  // digitalWrite(a_blue,HIGH);
  // read_sensor_values();

  // read_sensor_values();
  // followPath();

  // TCA9548A_tof_sensor(tof_front, 1);
  // TCA9548A_color_sensor(color_front);
  // Serial.println("for timing fix");
  // TCA9548A_gyro(gyro,1);
  
  // Rest of your loop

  // TCA9548A_gyro(gyro,3);
  // Serial.print("this   ");
  
  // delay(5000);
  // count_encoder(6);

  // dominant_front_color = TCA9548A_color_sensor(color_front);
  // Serial.print("Dominant color: ");
  // Serial.println(dominant_front_color);
  // Serial.println(" ");
  // delay(2000);


  // dominant_down_left_color = TCA9548A_color_sensor(color_down_left);
  // Serial.print("Dominante color 1");
  // Serial.println(dominant_down_left_color); 
  // Serial.println(" ");
  // delay(2000);


  // dominant_down_right_color = TCA9548A_color_sensor(color_down_right);
  // Serial.print("Dominante color 2");
  // Serial.println(dominant_down_right_color);
  // Serial.println(" ");
  // junction_count = 12;
  // followPath();
  // delay(20000);

  // if(digitalRead(metal_out) ==1){
  // digitalWrite(b_red ,HIGH);
  // delay(1000);
  // digitalWrite(b_red,LOW);
  // delay(1000);
  // }
  // delay(5000);
  // count_encoder(-0.85);
  // analogWrite(leftmotor_pwm, 150); //Left Motor Speed
  // analogWrite(rightmotor_pwm, 188); //Right Motor Speed
  // forward();
  // delay(2000);
  // stop_bot();
  // delay(2000);
  // calibrateReverseSensors();
  // delay(5000);

}



