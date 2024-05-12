
#include "sharp_ir.h"

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

// Constants for the Sharp IR sensor
const int sensorPin[] = {A0}; // Pin connected to the sensor
const int AVERAGE_OF = 5; // Number of readings to average
const int MAX_READINGS = 100; // Maximum number of readings to store
float distance[MAX_READINGS]; // Array to store distance readings
float Variance[6] = {0,0,0,0,0,0}; // Array to store distance readings
int numReadings = 0; // Number of readings taken
const float MCU_VOLTAGE = 4.96; // Voltage supplied to the microcontroller
int currentSize = 0; 

void readDistance(int sensor) {
  float voltageTempAverage = 0; // Temporary variable to store average voltage

  // Read multiple values and average them
  for (int i = 0; i < AVERAGE_OF; i++) {
    int sensorValue = analogRead(sensorPin[sensor]); // Read sensor value
    delay(1); // Delay for stability
    voltageTempAverage += sensorValue * (MCU_VOLTAGE / 1023.0); // Convert to voltage
  }
  voltageTempAverage /= AVERAGE_OF; // Calculate the average voltage

  // Use the equation of the fitting curve to calculate distance
  distance[numReadings] = 33.9 - 69.5 * voltageTempAverage + 62.3 * pow(voltageTempAverage, 2) - 25.4 * pow(voltageTempAverage, 3) + 3.83 * pow(voltageTempAverage, 4);
  numReadings++; // Increment the number of readings
}

float calculateStatistics() {
  float sum = 0;
  float mean;
  float variance = 0;
  
  // Calculate the sum of the distances
  for (int i = 0; i < numReadings; i++) {
    sum += distance[i];
  }
  
  // Calculate the mean
  mean = sum / numReadings;
  
  // Calculate the variance
  for (int i = 0; i < numReadings; i++) {
    variance += pow(distance[i] - mean, 2);
  }
  variance /= numReadings;
  
  // Print the variance and standard deviation
  Serial.print("Variance: ");
  Serial.println(variance);
  Serial.print("Standard Deviation: ");
  Serial.println(sqrt(variance));
  // appendToVariance(variance);
  return variance;

}

// void appendToVariance(float newValue) {
//     if (currentSize < 6 ) {
//         Variance[currentSize] = newValue;
//         currentSize++;
//     } else {
//         // Array is full, handle error or resize if needed
//     }
// }


void sharp_ir_loop() {
  readDistance(0); // Read distance from sensor 1

  // Print the distance readings
  Serial.print("Distance: ");
  Serial.print(distance[numReadings - 1]); // Print the latest reading
  Serial.println(" cm");
  Serial.println(numReadings);
  
  // Check if the circle is complete
  // if (numReadings%100 ==0) {
  //   // Perform actions if the circle is complete
  //   calculateStatistics();
  // }
  
  // delay(300); // Delay for stability
}

void sharp_ir_ultra_loop() {
  delay(40); 
  
  float sum = 0.0; 
  int zeroCount = 0; // Counter for zero readings
  for (int i = 0; i < AVERAGE_OF; i++) {
    float reading = sonar.ping_cm(); 
    if (reading == 0.0) {
      zeroCount++; // Increment zero count
    } else {
      sum += reading;
    }
    delay(10); 
  }
  
  // If too many zero readings, skip storing the value
  if (zeroCount < AVERAGE_OF) {
    float averageDistance = sum / (AVERAGE_OF - zeroCount); 
    distance[numReadings] = averageDistance; 
    numReadings = (numReadings + 1) % MAX_READINGS; 
    Serial.print("Ping: ");
    Serial.print(averageDistance); 
    Serial.println("cm");
  } else {
    Serial.println("Too many zero readings, skipping storing the value.");
  }
  
  // // Print the array
  // Serial.println("Distance Array:");
  // for (int i = 0; i < MAX_READINGS; i++) {
  //   Serial.print(distance[i]);
  //   Serial.print(" ");
  // }
  // Serial.println();
}

