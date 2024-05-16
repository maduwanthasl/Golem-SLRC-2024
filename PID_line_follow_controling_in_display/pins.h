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

//Define encoder pins
extern const int ENCA; // YELLOW
extern const int ENCB; // WHITE

#define numSensors 12 // Define the number of sensors as a preprocessor macro

extern const int sensorPins[numSensors]; // Sensor array

//display
extern const int SCREEN_WIDTH ;
extern const int SCREEN_HEIGHT ;
extern const int OLED_RESET ;

extern const int outputA ;
extern const int outputB ;
extern const int btn;

#endif
