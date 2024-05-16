#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H
#include <Arduino.h>
#include "pins.h"
#include "calibrate_sensor.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

extern Adafruit_SSD1306 display;
extern int counter;
extern int aState;
extern int aLastState;
extern bool btnPressed;
extern unsigned long lastButtonPressTime;
extern const unsigned long doublePressDelay;
extern bool calibrationCompleteFlag;

enum MenuState {
  MAIN_MENU,
  CALIBRATION_MENU,
  CALIBRATION_START,
  CALIBRATION_SAVE,
  PID_MENU,
  GO,
  PID_KP,
  PID_KD,
  PID_KI
};

extern MenuState currentMenu;
extern MenuState mainMenuPrevious;
extern MenuState calibrationMenuPrevious;
extern MenuState pidMenuPrevious;

void setupDisplay();
void displayMainMenu();
void displayCalibrationMenu();
void displayPIDMenu();
void handleMenuSelection(int menuItem);
void returnToPreviousMenu();
void loopDisplay();


#endif