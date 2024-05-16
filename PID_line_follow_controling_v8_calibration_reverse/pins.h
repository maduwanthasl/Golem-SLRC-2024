#ifndef PINS_H
#define PINS_H
#include <Arduino.h>

// Define motor pins
extern const int leftmotor_pwm;
extern const int rightmotor_pwm;
extern const int leftForward;
extern const int rightForward;
extern const int leftBackward;
extern const int rightBackward;

// Define LED pins
extern const int a_blue;
extern const int a_green;
extern const int b_blue;
extern const int b_green;
extern const int b_red;

//Ultra sonic sensor
extern const int TRIGGER_PIN ;  // Arduino pin tied to trigger pin on the ultrasonic sensor.
extern const int ECHO_PIN  ;  // Arduino pin tied to echo pin on the ultrasonic sensor.
extern const int MAX_DISTANCE ; // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.


//Define encoder pins
extern const int ENCA; // YELLOW
extern const int ENCB; // WHITE
extern const int ENCC; // YELLOW
extern const int ENCD; // WHITE

#define numSensors 12 // Define the number of sensors as a preprocessor macro
#define numReverseSensors 6

extern const int sensorPins[numSensors]; // Sensor array

//display
extern const int SCREEN_WIDTH ;
extern const int SCREEN_HEIGHT ;
extern const int OLED_RESET ;

extern const int outputA ;
extern const int outputB ;
extern const int btn;

extern int metal_out;

#endif
