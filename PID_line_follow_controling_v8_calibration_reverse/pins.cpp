#include "pins.h"

// Define motor pins
const int leftmotor_pwm = 9;
const int rightmotor_pwm = 8;
const int leftForward = 26;
const int rightForward = 22;
const int leftBackward = 28;
const int rightBackward = 24;

// Define LED pins
const int a_blue = 36;
const int a_green =38;
const int b_blue = 40;
const int b_green =42;
const int b_red =44;

//Ultra sonic sensor
const int TRIGGER_PIN  = 23; // Arduino pin tied to trigger pin on the ultrasonic sensor.
const int ECHO_PIN     = 25;// Arduino pin tied to echo pin on the ultrasonic sensor.
const int MAX_DISTANCE = 40; // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.


//Define encoder pins
const int ENCA = 19; // YELLOW
const int ENCB = 18; // WHITE
const int ENCC = 3; // YELLOW
const int ENCD = 2; // WHITE

// Define IR sensor pins
const int sensorPins[numSensors] = {A7, A6, A15, A14, A13, A12, A11, A10, A9, A8, A5, A4};


//display,
const int SCREEN_WIDTH = 128;
const int SCREEN_HEIGHT = 64;
const int OLED_RESET = -1;

const int outputA =43 ;
const int outputB = 47;
const int btn = 49 ;

int metal_out = 27;