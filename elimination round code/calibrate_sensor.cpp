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
    analogWrite(leftmotor_pwm,105);
    analogWrite(rightmotor_pwm,105);
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


// Function to save threshold values to EEPROM for reverse sensors
void saveThresholdToEEPROMreverse() {
  int address = 0; // Starting EEPROM address to write the data

  // Write threshold values to EEPROM
  for (int i = 0; i < numReverseSensors; i++) {
    EEPROM.put(address, reverseThreshold[i]); // Write threshold value to EEPROM
    address += sizeof(int); // Increment address for next threshold value
  }
}

// Function to read threshold values from EEPROM for reverse sensors
void readThresholdFromEEPROMreverse() {
  int address = 0; // Starting EEPROM address to read the data

  // Read threshold values from EEPROM
  for (int i = 0; i < numReverseSensors ; i++) {
    EEPROM.get(address, reverseThreshold[i]); // Read threshold value from EEPROM
    address += sizeof(int); // Increment address for next threshold value
  }
}

void calibrateReverseSensors() {
  Serial.println("Calibrating reverse sensors...");
  
  // Initialize minValues and maxValues arrays
  for (int i = 0; i < numReverseSensors; i++) {
    reverseMinValues[i] = 1023; // Initialize with maximum possible value
    reverseMaxValues[i] = 0; // Initialize with minimum possible value
  }

  // Move motors to calibrate sensors
  for (int i = 0; i < 12000; i++) { // Adjust the loop count and motor speeds as needed
    analogWrite(leftmotor_pwm, 105);
    analogWrite(rightmotor_pwm, 105);
    digitalWrite(leftBackward, HIGH); // Assuming reverse array needs to move backward
    digitalWrite(rightForward, HIGH); // Assuming reverse array needs to move backward
    for (int sensorIndex = 0; sensorIndex < numReverseSensors; sensorIndex++) {
      // Select the channel on the multiplexer
      selectChannel(sensorIndex);

      // Read the sensor value from the multiplexer
      int sensorValue = analogRead(reverseSensorPins[sensorIndex]);

      // Update min and max values
      reverseMinValues[sensorIndex] = min(reverseMinValues[sensorIndex], sensorValue);
      reverseMaxValues[sensorIndex] = max(reverseMaxValues[sensorIndex], sensorValue);
    }
  }


  // Stop motors
  analogWrite(leftmotor_pwm, 0);
  analogWrite(rightmotor_pwm, 0);
  stop_bot();

  // Calculate thresholds
  for (int i = 0; i < numReverseSensors; i++) {
    reverseThreshold[i] = (reverseMinValues[i] + reverseMaxValues[i]) / 2;
  }

  Serial.println("Reverse sensor thresholds:");
  for (int i = 0; i < numReverseSensors; i++) {
    Serial.print("Sensor ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.println(reverseThreshold[i]);
  }
  Serial.println("Reverse Calibration complete.");
}
