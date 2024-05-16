#include "oled_display.h"
unsigned long calibrationCompleteTime = 0;
bool calibrationCompleteFlag = false;


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
int counter = 1;
int aState;
int aLastState;
bool btnPressed = false;
unsigned long lastButtonPressTime = 0;
const unsigned long doublePressDelay = 500; // Adjust as needed
MenuState currentMenu = MAIN_MENU;
MenuState mainMenuPrevious = MAIN_MENU;
MenuState calibrationMenuPrevious = MAIN_MENU;
MenuState pidMenuPrevious = MAIN_MENU;


void setupDisplay() {
  pinMode(outputA, INPUT);
  pinMode(outputB, INPUT);
  pinMode(btn, INPUT_PULLUP);

  Serial.begin(9600);
  aLastState = digitalRead(outputA);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}


void loopDisplay() {

  int btnState = digitalRead(btn);
  unsigned long currentTime = millis();

  if (btnState == LOW && !btnPressed) {
    if (currentTime - lastButtonPressTime < doublePressDelay) {
      returnToPreviousMenu();
    } else {
      btnPressed = true;
      lastButtonPressTime = currentTime;
      delay(100); // Debounce delay
      handleMenuSelection(counter);
    }
  } else if (btnState == HIGH) {
    btnPressed = false;
  }

  aState = digitalRead(outputA);
  if (aState != aLastState) {
    if (digitalRead(outputB) != aState) {
      counter++;
    } else {
      counter--;
    }
    if (currentMenu == MAIN_MENU) {
      if (counter < 1) counter = 1;
      if (counter > 3) counter = 3;
    } else if (currentMenu == CALIBRATION_MENU) {
      if (counter < 1) counter = 1;
      if (counter > 2) counter = 2;
    } else if (currentMenu == PID_MENU) {
      if (counter < 1) counter = 1;
      if (counter > 3) counter = 3;
    }
    // Serial.print("Position: ");
    // Serial.println(counter);
  }
  aLastState = aState;

  display.setTextColor(SSD1306_WHITE);
  display.clearDisplay();

  switch (currentMenu) {
    case MAIN_MENU:
      displayMainMenu();
      break;
    case CALIBRATION_MENU:
      displayCalibrationMenu();
      break;
    case CALIBRATION_START:
      if (!calibrationCompleteFlag) { // If calibration is not complete
        display.setTextSize(1);
        display.setCursor(0, 0);
        display.println("Calibration: Start");
        // Add your code for "Start" calibration here
        delay(1000);
        calibrateSensors();
        delay(1000);
        calibrateReverseSensors();
        display.setTextSize(1);
        display.setCursor(0, 10);
        display.println("Calibration complete.");
        calibrationCompleteTime = millis(); // Record the time when calibration is complete
        calibrationCompleteFlag = true; // Set the flag indicating calibration is complete

      }
      if (millis() - calibrationCompleteTime >= 3000) { // Wait for 3 seconds after calibration complete
        currentMenu = MAIN_MENU; // Switch back to MAIN_MENU after 3 seconds
      }
      break;
    case CALIBRATION_SAVE:
      if (calibrationCompleteFlag) { // If calibration is not complete
        display.setTextSize(1);
        display.setCursor(0, 0);
        display.println("Calibration: Save to EEPROM");
        // Add your code for "Save to EEPROM" calibration here
        // Save thresholds to EEPROM
        saveThresholdToEEPROM();
        saveThresholdToEEPROMreverse();

        readThresholdFromEEPROM();
        readThresholdFromEEPROMreverse();
        // Print threshold values on the OLED display
        display.setTextSize(1);
        display.setCursor(0, 10);
        display.println("Threshold values:");

        // for (int i = 0; i < numSensors; i++) {
        //   display.setCursor(0, 20 + i * 10);
        //   display.print("Sensor ");
        //   display.print(i + 1);
        //   display.print(": ");
        //   display.println(threshold[i]);
        // }

        calibrationCompleteTime = millis(); // Record the time when calibration is complete
        calibrationCompleteFlag = false; // Set the flag indicating calibration is complete
        delay(3000);
        }
        if (millis() - calibrationCompleteTime >= 3000) { // Wait for 3 seconds after calibration complete
          currentMenu = MAIN_MENU; // Switch back to MAIN_MENU after 3 seconds
       }
      break;
    case PID_MENU:
      displayPIDMenu();
      break;
    case PID_KP:
      display.setTextSize(1);
      display.setCursor(0, 0);
      display.println("PID: KP");
      // Add your code for PID control here
      break;
    case PID_KD:
      display.setTextSize(1);
      display.setCursor(0, 0);
      display.println("PID: KD");
      // Add your code for PID control here
      break;
    case PID_KI:
      display.setTextSize(1);
      display.setCursor(0, 0);
      display.println("PID: KI");
      // Add your code for PID control here
      break;
    case GO:
      display.setTextSize(1);
      display.setCursor(0, 0);
      display.println("GO");
      // Add your code for run the robot here
      followPath();
      break;
  }

  display.display();
}



void displayMainMenu() {
  int textWidth = 12 * 5;
  int x = (SCREEN_WIDTH - textWidth) / 2;
  display.setTextSize(2);
  display.setCursor(x, 0);
  display.println("GOLEM");

  display.setTextSize(1);
  display.setCursor(20, 25);
  if (counter == 1) {
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Highlight selected item
  } else {
    display.setTextColor(SSD1306_WHITE);
  }
  display.println("1. Calibration");
  display.setTextColor(SSD1306_WHITE); // Reset color
  display.setCursor(20, 35);
  if (counter == 2) {
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Highlight selected item
  } else {
    display.setTextColor(SSD1306_WHITE);
  }
  display.println("2. PID Control");
  display.setTextColor(SSD1306_WHITE); // Reset color
  display.setCursor(20, 45);
  if (counter == 3) {
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Highlight selected item
  } else {
    display.setTextColor(SSD1306_WHITE);
  }
  display.println("3. GO");
}


void displayCalibrationMenu() {
  int textWidth = 6 * 11;
  int x = (SCREEN_WIDTH - textWidth) / 2;
  display.setTextSize(1);
  display.setCursor(x, 0);
  display.println("CALIBRATION");

  display.setTextSize(1);
  display.setCursor(20, 25);
  if (counter == 1) {
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Highlight selected item
  } else {
    display.setTextColor(SSD1306_WHITE);
  }
  display.println("1. Start");
  display.setTextColor(SSD1306_WHITE); // Reset color
  display.setCursor(20, 35);
  if (counter == 2) {
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Highlight selected item
  } else {
    display.setTextColor(SSD1306_WHITE);
  }
  display.println("2. Save to EEPROM");
}

void displayPIDMenu() {
  int textWidth = 6 * 11;
  int x = (SCREEN_WIDTH - textWidth) / 2;
  display.setTextSize(1);
  display.setCursor(x, 0);
  display.println("PID CONTROL");

  display.setTextSize(1);
  display.setCursor(20, 25);
  if (counter == 1) {
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Highlight selected item
  } else {
    display.setTextColor(SSD1306_WHITE);
  }
  display.println("1. KP");
  display.setTextColor(SSD1306_WHITE); // Reset color
  display.setCursor(20, 35);
  if (counter == 2) {
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Highlight selected item
  } else {
    display.setTextColor(SSD1306_WHITE);
  }
  display.println("2. KD");
  display.setTextColor(SSD1306_WHITE); // Reset color
  display.setCursor(20, 45);
  if (counter == 3) {
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Highlight selected item
  } else {
    display.setTextColor(SSD1306_WHITE);
  }
  display.println("3. KI");
}




void handleMenuSelection(int menuItem) {
  switch (currentMenu) {
    case MAIN_MENU:
      if (menuItem == 1) {
        mainMenuPrevious = currentMenu;
        currentMenu = CALIBRATION_MENU;
        counter = 1; // Reset counter for sub-menu
      } else if (menuItem == 2) {
        mainMenuPrevious = currentMenu;
        currentMenu = PID_MENU;
        counter = 1; // Reset counter for sub-menu
      } else if (menuItem == 3) {
        mainMenuPrevious = currentMenu;
        currentMenu = GO;
        counter = 1; // Reset counter for sub-menu
      }
      break;
    case CALIBRATION_MENU:
      if (menuItem == 1) {
        calibrationMenuPrevious = currentMenu;
        currentMenu = CALIBRATION_START;
      } else if (menuItem == 2) {
        calibrationMenuPrevious = currentMenu;
        currentMenu = CALIBRATION_SAVE;
      }
      break;
    case PID_MENU:
      if (menuItem == 1) {
        pidMenuPrevious = currentMenu;
        currentMenu = PID_KP;
      } else if (menuItem == 2) {
        pidMenuPrevious = currentMenu;
        currentMenu = PID_KD;
      } else if (menuItem == 3) {
        pidMenuPrevious = currentMenu;
        currentMenu = PID_KI;
      }
      break;
    default:
      break;
  }
}

void returnToPreviousMenu() {
  switch (currentMenu) {
    case MAIN_MENU:
      // Cannot go back from main menu
      break;
    case CALIBRATION_MENU:
      currentMenu = mainMenuPrevious;
      break;
    case CALIBRATION_START:
    case CALIBRATION_SAVE:
      currentMenu = calibrationMenuPrevious;
      break;
    case PID_MENU:
      currentMenu = mainMenuPrevious;
      break;
    case PID_KP:
    case PID_KD:
    case PID_KI:
      currentMenu = pidMenuPrevious;
      break;
    default:
      break;
  }
}

