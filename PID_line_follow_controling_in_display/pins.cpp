#include "pins.h"

// Define motor pins
const int leftmotor_pwm = 9;
const int rightmotor_pwm = 8;
const int leftForward = 26;
const int rightForward = 22;
const int leftBackward = 28;
const int rightBackward = 24;

//Define encoder pins
const int ENCA = 2; // YELLOW
const int ENCB = 3; // WHITE

// Define IR sensor pins
const int sensorPins[numSensors] = {A7, A6, A15, A14, A13, A12, A11, A10, A9, A8, A5, A4};


//display,
const int SCREEN_WIDTH = 128;
const int SCREEN_HEIGHT = 64;
const int OLED_RESET = -1;

const int outputA =30 ;
const int outputB = 32;
const int btn = 34 ;