# Golem - SLRC 2024

Welcome to the Golem-SLRC-2024 repository! This project showcases my participation in the Sri Lanka Robotic Challenge (SLRC) 2024, organized by the Electronic Club at the University of Moratuwa. I participated as an individual team member and successfully completed the elimination round, securing a place in the final round. This repository contains the final code, design files, and documentation for my robot, Golem.

![task](https://github.com/user-attachments/assets/8448ebd2-c201-4513-b358-25d4ffca28a5)


## Project Overview

Golem is a line-following robot designed to navigate complex paths and perform various tasks autonomously. The robot was built using an Arduino Mega board, various sensors, motor drivers, and custom-designed components. A notable feature of Golem is its robotic arm, which I designed and 3D printed using my Imagineer 3D printer. This document provides a detailed overview of the project's development, including the design, implementation, and functionality of Golem.

## Table of Contents
- [Project Overview](#project-overview)
- [Hardware Components](#hardware-components)
- [Software Components](#software-components)
- [Robot Design](#robot-design)
- [Functionality](#functionality)
- [Code Segments](#code-segments)
- [Photos](#photos)
- [Acknowledgements](#acknowledgements)

## Hardware Components

- Arduino Mega Board
- 14 IR Sensors Array
- L298N Motor Driver
- 12V LiPo Battery
- Buck Converters (LM2596)
- TOF Sensor (Time of Flight)
- OLED Display
- Rotary Encoder
- TCS34725 Color Sensor Module
- Ultrasonic Sensor
- MG995 Servo Motor
- Hobby Servo Motor
- Custom 3D Printed Parts (using Imagineer 3D Printer)
- Acrylic Sheets for Chassis

## Software Components

The software for Golem was developed using Arduino IDE, and the code is organized into several sub-functions to handle different tasks:

- Forward Line Following
- Reverse Line Following
- IR Sensor Calibration
- EEPROM Read/Write
- TOF Distance Measurement
- Color Detection
- Object Detection
- Robotic Arm Control

## Robot Design

In the initial stage, I constructed the robot chassis using acrylic sheets and purchased various components. The design process involved categorizing all functions into sub-functions and developing them within a specified time frame.

### Sub-Tasks

1. **Forward Line Following**: Using a 14 IR sensor array to follow lines.
2. **Distance Measurement**: Adding a TOF sensor to measure distance.
3. **Function Control**: Using an OLED display and rotary encoder to control functions.
4. **IR Sensor Calibration**: Developing calibration code for the IR arrays.
5. **Reverse Line Following**: Adding a reverse IR array for reverse functions and junction detection.
6. **EEPROM Storage**: Implementing EEPROM read/write functions for calibration values.
7. **Color Detection**: Using a TCS34725 color sensor module for junction color detection.
8. **Object Detection**: Adding an ultrasonic sensor for object detection and differentiation between cuboid and cylinder.
9. **Robotic Arm**: Constructing a simple 2-DOF robotic arm to pick up metal boxes.

## Functionality

## Software Components

The software for Golem was developed in a modular approach, where each functionality was divided into sub-functions and implemented step-by-step. The key functionalities include:

### 1. Forward Line Following using 14 IR Sensors

I used 14 IR sensors to develop the line-following task. The IR sensors detect the path, and the robot adjusts its movement accordingly using the L298N motor driver. The 12V LiPo battery provides the necessary power, and buck converters (LM2596) ensure stable voltage for the components.

#### Sensor calibration
```cpp
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
```

```cpp
void read_sensor_values()
{
  readThresholdFromEEPROM();
  // White == 1 & Black == 0 left - , right +
  for (int sensorIndex = 0; sensorIndex < numSensors; sensorIndex++) {
    sensorValues[sensorIndex] = analogRead(sensorPins[sensorIndex]);
    if (sensorValues[sensorIndex] > threshold[sensorIndex]) {
        sensorValues[sensorIndex] = 0;
    } else {
        sensorValues[sensorIndex] = 1;
    }
  }

  int expectedValues[][numSensors] = {
    // Add your expected values here
  };

  int errorValues[] = {
    // Add your error values here
  };

  bool conditionMet = false;
  int defaultErrorValue = 0;

  for (int condIndex = 0; condIndex < sizeof(expectedValues) / sizeof(expectedValues[0]); condIndex++) {
    conditionMet = true;
    for (int sensorIndex = 0; sensorIndex < numSensors; sensorIndex++) {
      if (expectedValues[condIndex][sensorIndex] != -1 && sensorValues[sensorIndex] != expectedValues[condIndex][sensorIndex]) {
        conditionMet = false;
        break;
      }
    }
    if (conditionMet) {
      error = errorValues[condIndex];
      if (condIndex >= sizeof(errorValues) / sizeof(errorValues[0]) - 13) {
        motor_pos = 0; motor_pos2 = 0;
        count_encoder(0.45);
        junction_count++;
        motor_pos = 0; motor_pos2 = 0;
        Serial.println(junction_count);
      }
      break;
    }
  }

  if (!conditionMet) {
    error = defaultErrorValue;
  }
}
```

### 2. TOF Sensor Integration for Distance Measurement

A Time of Flight (TOF) sensor was added to measure the distance accurately. This helps the robot navigate and avoid obstacles.

```cpp
#include "measure_distance_tof.h"

static Adafruit_VL53L0X lox = Adafruit_VL53L0X();


void measure_distance_tof_setup() {
  Serial.begin(9600);

  // Wait until serial port opens for native USB devices
  while (!Serial) {
    delay(1);
  }

  Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  // Power 
  Serial.println(F("VL53L0X API Simple Ranging example\n\n"));
}



void measure_distance_tof_loop(int Samples) {
  VL53L0X_RangingMeasurementData_t measure;
  unsigned long totalDistance = 0; // Variable to store the total distance
  int numSamples = Samples ; // Number of samples to average

  for (int i = 0; i < numSamples; i++) {
    lox.rangingTest(&measure, false); // Perform distance measurement
    if (measure.RangeStatus != 4) {  // Phase failures have incorrect data
      totalDistance += measure.RangeMilliMeter; // Add the distance measurement to the total
    }
    delay(50); // Wait a short time between measurements
  }

  // Compute the average distance
  distance_tof = totalDistance / numSamples;

  Serial.print("Average Distance (mm): ");
  Serial.println(distance_tof);
  return;

}
```

### 3. OLED Display and Rotary Encoder for Control

An OLED display was added to provide real-time information about the robot's status. The rotary encoder allows for easy navigation through different functions and settings on the display, making the robot more user-friendly.

### 4. IR Array Calibration

Calibration code for the IR arrays was developed to ensure accurate line following. Here is a sample of the calibration code:

### 5. Reverse Function and Junction Detection
A reverse IR array was added to enable the robot to move backward and detect junctions. Calibration code was also implemented for the reverse sensors. The calibrated values are stored in the EEPROM for quick access.

### 6. EEPROM Read and Write
I developed code to read and write calibration values to the EEPROM. This ensures that the robot retains its calibration settings even after power cycles.

### 7. Color Detection using TCS34725
A TCS34725 color sensor module was mounted below the robot to detect color junctions on the path. This sensor helps the robot identify different colored markers on the track.

### 8. Ultrasonic Sensor for Object Detection
An ultrasonic sensor was used to detect objects within a circle. The sensor measures the distance and helps identify whether the object is a cuboid or a cylinder based on the variance in the measurements.

### 9. Robotic Arm with 2 DOF
I designed a simple robotic arm with two degrees of freedom (DOF) to pick up objects. The arm uses an MG995 servo motor and a hobby servo motor. The arm design was created using CAD software and 3D printed using my Imagineer 3D printer.

### Forward Line Following Reading Sensor Valu
