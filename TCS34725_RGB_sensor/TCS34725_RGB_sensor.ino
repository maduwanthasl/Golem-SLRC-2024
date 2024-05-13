#include <Wire.h>
#include "Adafruit_TCS34725.h"

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

int redCount = 0;
int greenCount = 0;
int blueCount = 0;

unsigned long startTime = 0;

void setup() {
  Serial.begin(9600);

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found, check connections");
    while (1);
  }
}

void loop() {
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);

  // Subtract from the red value
  r -= 55;
  
  if (millis() - startTime < 5000) { // Collect samples for 5 seconds

    if (r > g && r > b) {
      redCount++;
    } else if (g > r && g > b) {
      greenCount++;
    } else if (b > r && b > g) {
      blueCount++;
    }
    
    delay(10); // delay between each sample
  } else { // After 5 seconds, determine the dominant color
    Serial.print("Red Count: "); Serial.print(redCount); Serial.print("\t");
    Serial.print("Green Count: "); Serial.print(greenCount); Serial.print("\t");
    Serial.print("Blue Count: "); Serial.println(blueCount);

    if (redCount > greenCount && redCount > blueCount) {
      Serial.println("Dominant Color: Red");
    } else if (greenCount > redCount && greenCount > blueCount) {
      Serial.println("Dominant Color: Green");
    } else if (blueCount > redCount && blueCount > greenCount) {
      Serial.println("Dominant Color: Blue");
    } else {
      Serial.println("Dominant Color: Unknown");
    }
    
    // Reset counts for the next iteration
    redCount = 0;
    greenCount = 0;
    blueCount = 0;
    
    // Reset the timer for the next 5 seconds
    startTime = millis();
    while (true) {
        // Do nothing, effectively stopping the loop.
    }
  }
}
