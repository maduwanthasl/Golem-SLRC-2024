#include <NewPing.h>

#define TRIGGER_PIN  3  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     4  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 30 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

const int AVERAGE_OF = 5;       // Number of readings to average
const int MAX_READINGS = 50;   // Maximum number of readings to store
float distance[MAX_READINGS];   // Array to store distance readings
int currentIndex = 0;           // Index to keep track of current position in the array

void setup() {
  Serial.begin(9600); // Open serial monitor at 115200 baud to see ping results.
}

void loop() {
  delay(50); // Wait 40ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  
  float sum = 0.0; // Variable to store the sum of samples
  for (int i = 0; i < AVERAGE_OF; i++) {
    sum += sonar.ping_cm(); // Accumulate readings
    delay(10); // Wait between individual readings
  }
  
  float averageDistance = sum / AVERAGE_OF; // Calculate average distance
  
  distance[currentIndex] = averageDistance; // Store the average distance in the array
  currentIndex = (currentIndex + 1) % MAX_READINGS; // Move to the next index, loop back to 0 if reached the end
  
  Serial.print("Ping: ");
  Serial.print(averageDistance); // Print the average distance
  Serial.println("cm");

  if (currentIndex%100 ==0){
  // Print the array
  Serial.println("Distance Array:");
  for (int i = 0; i < MAX_READINGS; i++) {
    Serial.print(distance[i]);
    Serial.print(" ");
    calculateStatistics();
  }
  Serial.println();
  }
}


float calculateStatistics() {
  float sum = 0;
  float mean;
  float variance = 0;
  
  // Calculate the sum of the distances
  for (int i = 0; i < currentIndex; i++) {
    sum += distance[i];
  }
  
  // Calculate the mean
  mean = sum / currentIndex;
  
  // Calculate the variance
  for (int i = 0; i < currentIndex; i++) {
    variance += pow(distance[i] - mean, 2);
  }
  variance /= currentIndex;
  
  // Print the variance and standard deviation
  Serial.print("Variance: ");
  Serial.println(variance);
  Serial.print("Standard Deviation: ");
  Serial.println(sqrt(variance));
  // appendToVariance(variance);
  return variance;

}
