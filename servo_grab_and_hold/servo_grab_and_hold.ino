#include <Servo.h>

Servo MG995;  // create servo object to control a servo
Servo MG90;   // create another servo object

int pos = 0;    // variable to store the servo position

void setup() {
  MG995.attach(10);  // attaches the servo on pin 10 to the MG995 servo object
  MG90.attach(11);   // attaches the servo on pin 11 to the MG90 servo object

  // Set initial position to 150 degrees
  MG995.write(150);
  MG90.write(110);
}

void loop() {
  // Open gripper (move MG995 servo from 150 to 50 position)
  for (int pos = 150; pos >= 40; pos -= 1) {
    MG995.write(pos);    // move MG995 servo to position 'pos'
    delay(15);           // wait for servo to reach position
  }
  delay(500);  // wait for 0.5 seconds after fully opening gripper
  
  // Lower gripper (move MG90 servo from 110 to 60 position)
  for (int pos = 110; pos >= 60; pos -= 1) {
    MG90.write(pos);     // move MG90 servo to position 'pos'
    delay(15);           // wait for servo to reach position
  }
  delay(5000);  // wait for 0.5 seconds after lowering gripper
  
  // Close gripper (move MG995 servo from 50 to 150 position)
  for (int pos = 40; pos <= 150; pos += 1) {
    MG995.write(pos);    // move MG995 servo to position 'pos'
    delay(15);           // wait for servo to reach position
  }
  delay(500);  // wait for 0.5 seconds after fully closing gripper
  
  // Lift gripper (move MG90 servo from 60 to 110 position)
  for (int pos = 60; pos <= 110; pos += 1) {
    MG90.write(pos);     // move MG90 servo to position 'pos'
    delay(15);           // wait for servo to reach position
  }
  delay(1000); // wait for 1 second after fully lifting gripper
  
  // Repeat the process to complete one cycle
}


