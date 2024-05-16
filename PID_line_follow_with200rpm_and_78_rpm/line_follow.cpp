#include "line_follow.h"

void followPath(){
  read_sensor_values();

  if (error == 100) {               // Make left turn untill it detects straight path
    do {
      read_sensor_values();
      analogWrite(leftmotor_pwm, 70); //Changed from ENA
      analogWrite(rightmotor_pwm, 70); //Changed from ENB
      sharpLeftTurn();
      // Serial.println("error == 100");
    } while (error != 0 && error != -1 && error != 1);

  } 
  else if (error == 101) {          // Make right turn in case of it detects only right path (it will go into forward direction in case of staright and right "|--")
                                      // untill it detects straight path.
    analogWrite(leftmotor_pwm, 70); //Changed from ENA
    analogWrite(rightmotor_pwm, 70); //Changed from ENB
    forward();
    delay(150);
    stop_bot();
    read_sensor_values();
    if (error == 102) {
      do {
        analogWrite(leftmotor_pwm, 70); //Changed from ENA
        analogWrite(rightmotor_pwm, 70); //Changed from ENB
        sharpRightTurn();
        read_sensor_values();
      } while (error != 0 && error != -1 && error != 1);
    }
  } 
  else if (error == 102) {        // Make left turn untill it detects straight path
    do {
      analogWrite(leftmotor_pwm, 70); //Changed from ENA
      analogWrite(rightmotor_pwm, 70); //Changed from ENB
      sharpLeftTurn();
      read_sensor_values();
      if (error == 0 || error == 1 || error == -1) {
        stop_bot();
        delay(200);
      }
    }  while (error != 0 && error != -1 && error != 1);
  } 
  else if (error == 103) { // Make left turn untill it detects straight path or stop if dead end reached.
    if (flag == 0) {
      analogWrite(leftmotor_pwm, 70); //Changed from ENA
      analogWrite(rightmotor_pwm, 70); //Changed from ENB
      forward();
      delay(200);
      stop_bot();
      read_sensor_values();
      if (error == 103) {     /**** Dead End Reached, Stop! ****/
        stop_bot();
        flag = 1;
      } else {        /**** Move Left ****/
        analogWrite(leftmotor_pwm, 70); //Changed from ENA
        analogWrite(rightmotor_pwm, 70); //Changed from ENB
        sharpLeftTurn();
        delay(200);
        do {
          read_sensor_values();
          analogWrite(leftmotor_pwm, 70); //Changed from ENA
          analogWrite(rightmotor_pwm, 70); //Changed from ENB
          sharpLeftTurn();
        } while (error != 0 && error != -1 && error != 1);
      }
    }
  } 
  else {
    calculate_pid();
    motor_control();
  }
}