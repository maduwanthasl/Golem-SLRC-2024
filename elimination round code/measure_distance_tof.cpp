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
