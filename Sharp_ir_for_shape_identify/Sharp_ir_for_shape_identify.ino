// Constants for the Sharp IR sensor
const int sensorPin[] = {A0}; // Pin connected to the sensor
const int AVERAGE_OF = 2; // Number of readings to average
const int MAX_READINGS = 100; // Maximum number of readings to store
float distance[MAX_READINGS]; // Array to store distance readings
int numReadings = 0; // Number of readings taken
const float MCU_VOLTAGE = 4.40; // Voltage supplied to the microcontroller

void setup() {
  Serial.begin(9600); // Start serial communication
  Serial.println("Robojax Sharp GP2Y0A51SK0F demo"); // Print a message
}

void loop() {
  readDistance(0); // Read distance from sensor 1

  // Print the distance readings
  Serial.print("Distance: ");
  Serial.print(distance[numReadings - 1]); // Print the latest reading
  Serial.println(" cm");
  
  // Check if the circle is complete
  if (numReadings ==100 ) {
    // Perform actions if the circle is complete
    calculateStatistics();
  }
  
  delay(300); // Delay for stability
}

/*
 * readDistance()
 * @brief Reads distance from Sharp sensor and updates the distance array
 * @param sensor: Sensor index
 */
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

/*
 * calculateStatistics()
 * @brief Calculates and prints the variance and standard deviation of the distance readings
 */
void calculateStatistics() {
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
}
