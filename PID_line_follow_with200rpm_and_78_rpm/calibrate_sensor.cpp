#include "calibrate_sensor.h"


/*-----------------------------------------------------------------------------------------------------------
----------------------------------------------SENSOR CALIBRATION---------------------------------------------
-----------------------------------------------------------------------------------------------------------*/

// Function to save threshold values to EEPROM
void saveThresholdToEEPROM() {
  int address = 0; // Starting EEPROM address to write the data

  // Write threshold values to EEPROM
  for (int i = 0; i < numSensors; i++) {
    EEPROM.put(address, threshold[i]); // Write threshold value to EEPROM
    address += sizeof(int); // Increment address for next threshold value
  }

}

// Function to read threshold values from EEPROM
void readThresholdFromEEPROM() {
  int address = 0; // Starting EEPROM address to read the data

  // Read threshold values from EEPROM
  for (int i = 0; i < numSensors ; i++) {
    EEPROM.get(address, threshold[i]); // Read threshold value from EEPROM
    address += sizeof(int); // Increment address for next threshold value
  }
}


void calibrateSensors() {
  Serial.println("Calibrating sensors...");
  
  // Initialize minValues and maxValues arrays
  for (int i = 0; i < numSensors; i++) {
    minValues[i] = 1023; // Initialize with maximum possible value
    maxValues[i] = 0; // Initialize with minimum possible value
  }

  // Move motors to calibrate sensors
  for (int i = 0; i < 12000; i++) { // Adjust the loop count and motor speeds as needed
    analogWrite(leftmotor_pwm,45);
    analogWrite(rightmotor_pwm,45);
    digitalWrite(leftForward,HIGH);
    digitalWrite(rightBackward,HIGH);
    for (int sensorIndex = 0; sensorIndex < numSensors; sensorIndex++) {
      int sensorValue = analogRead(sensorPins[sensorIndex]);
      minValues[sensorIndex] = min(minValues[sensorIndex], sensorValue);
      maxValues[sensorIndex] = max(maxValues[sensorIndex], sensorValue);
    }
  }

  // Stop motors
  analogWrite(leftmotor_pwm,0);
  analogWrite(rightmotor_pwm,0);
  stop_bot();


  // Calculate thresholds
  for (int i = 0; i < numSensors; i++) {
    threshold[i] = (minValues[i] + maxValues[i]) / 2;
  }

  // // Print thresholds
  // Serial.println("Sensor thresholds:");
  // for (int i = 0; i < numSensors; i++) {
  //   Serial.print("Sensor ");
  //   Serial.print(i + 1);
  //   Serial.print(": ");
  //   Serial.println(threshold[i]);
  // }
  // Serial.println("Calibration complete.");

  
  

}

/*------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------*/

