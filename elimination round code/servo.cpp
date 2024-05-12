#include "servo.h"

Servo MG995;  // create servo object to control a servo
Servo MG90;   // create another servo object

int pos = 0;    // variable to store the servo position

void servo_setup() {
  MG995.attach(10);  // attaches the servo on pin 10 to the MG995 servo object
  MG90.attach(11);   // attaches the servo on pin 11 to the MG90 servo object

  // Set initial position to 150 degrees
  MG995.write(150);
  MG90.write(110);
}

void mg995_down(){
  // Open gripper (move MG995 servo from 150 to 50 position)
  for (int pos = 150; pos >= 60; pos -= 1) {
    MG995.write(pos);    // move MG995 servo to position 'pos'
    delay(15);           // wait for servo to reach position
  }
  delay(500);  // wait for 0.5 seconds after fully opening gripper
}
void mg90_close(){
  // Lower gripper (move MG90 servo from 110 to 60 position)
  for (int pos = 110; pos >= 50; pos -= 1) {
    MG90.write(pos);     // move MG90 servo to position 'pos'
    delay(15);           // wait for servo to reach position
  }
  delay(500);  // wait for 0.5 seconds after lowering gripper

}

void mg995_up(){
  // Close gripper (move MG995 servo from 50 to 150 position)
  for (int pos = 60 ; pos <= 150; pos += 1) {
    MG995.write(pos);    // move MG995 servo to position 'pos'
    delay(15);           // wait for servo to reach position
  }
  delay(500);  // wait for 0.5 seconds after fully closing gripper
}

void mg90_open(){
  // Lift gripper (move MG90 servo from 60 to 110 position)
  for (int pos = 50; pos <= 110; pos += 1) {
    MG90.write(pos);     // move MG90 servo to position 'pos'
    delay(15);           // wait for servo to reach position
  }
  delay(1000); // wait for 1 second after fully lifting gripper
}

void mg995_down_2(){
  // Open gripper (move MG995 servo from 150 to 50 position)
  for (int pos = 60; pos >= 45; pos -= 1) {
    MG995.write(pos);    // move MG995 servo to position 'pos'
    delay(15);           // wait for servo to reach position
  }
  delay(500);  // wait for 0.5 seconds after fully opening gripper
}
void mg995_up_2(){
  // Close gripper (move MG995 servo from 50 to 150 position)
  for (int pos = 45; pos <= 60; pos += 1) {
    MG995.write(pos);    // move MG995 servo to position 'pos'
    delay(15);           // wait for servo to reach position
  }
  delay(500);  // wait for 0.5 seconds after fully closing gripper
}