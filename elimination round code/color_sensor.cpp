
// #include "color_sensor.h"

// Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

// int redCount = 0;
// int greenCount = 0;
// int blueCount = 0;

// unsigned long startTime = 0;

// void setup_color_sensor() {

//   if (tcs.begin()) {
//     Serial.println("Found sensor");
//   } else {
//     Serial.println("No TCS34725 found, check connections");
//     while (1);
//   }
// }

// void loop_color_sensor() {
//   uint16_t r, g, b, c;
  
//   if (millis() - startTime < 5000) { // Collect samples for 5 seconds
//     tcs.getRawData(&r, &g, &b, &c);

//     if (r > g && r > b) {
//       redCount++;
//     } else if (g > r && g > b) {
//       greenCount++;
//     } else if (b > r && b > g) {
//       blueCount++;
//     }
    
//     delay(10); // delay between each sample
//   } else { // After 5 seconds, determine the dominant color
//     Serial.print("Red Count: "); Serial.print(redCount); Serial.print("\t");
//     Serial.print("Green Count: "); Serial.print(greenCount); Serial.print("\t");
//     Serial.print("Blue Count: "); Serial.println(blueCount);

//     if (redCount > greenCount && redCount > blueCount) {
//       Serial.println("Dominant Color: Red");
//     } else if (greenCount > redCount && greenCount > blueCount) {
//       Serial.println("Dominant Color: Green");
//     } else if (blueCount > redCount && blueCount > greenCount) {
//       Serial.println("Dominant Color: Blue");
//     } else {
//       Serial.println("Dominant Color: Unknown");
//     }
    
//     // Reset counts for the next iteration
//     redCount = 0;
//     greenCount = 0;
//     blueCount = 0;
    
//     // Reset the timer for the next 5 seconds
//     startTime = millis();
//   }
// }



#include "color_sensor.h"

ColorSensor::ColorSensor() :
    tcs(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X),
    redCount(0), greenCount(0), blueCount(0){}

void ColorSensor::setup() {
    if (tcs.begin()) {
        Serial.println("Found sensor");
    } else {
        Serial.println("No TCS34725 found, check connections");
        while (1);
    }
}

void ColorSensor::loop() {
    const int numSamples = 5; // Number of samples to collect
    int sampleCount = 0;
    dominantColor = "Unknown";

    do {
        uint16_t r, g, b, c;
        tcs.getRawData(&r, &g, &b, &c);

        // Subtract from the red value
        r -= 0;
        Serial.println(r);
        Serial.println(g);
        Serial.println(b);
        


        if (sampleCount < numSamples) { // Collect numSamples samples

            if (r > g && r > b) {
                redCount++;
            } else if (g > r && g > b) {
                greenCount++;
            } else if (b > r && b > g) {
                blueCount++;
            }

            Serial.print(redCount); Serial.print(", ");
            Serial.print(greenCount); Serial.print(", ");
            Serial.println(blueCount);

            sampleCount++;
            delay(10); // delay between each sample
        } else { // After collecting numSamples, determine the dominant color
            Serial.print("Red Count: "); Serial.print(redCount); Serial.print("\t");
            Serial.print("Green Count: "); Serial.print(greenCount); Serial.print("\t");
            Serial.print("Blue Count: "); Serial.println(blueCount);

            if (redCount > greenCount && redCount > blueCount) {
                dominantColor = "Red";
            } else if (greenCount > redCount && greenCount > blueCount) {
                dominantColor = "Green";
            } else if (blueCount > redCount && blueCount > greenCount) {
                dominantColor = "Blue";
            } else {
                dominantColor = "Unknown";
            }

            // Print the dominant color
            Serial.print("Dominant Color: "); Serial.println(dominantColor);
            
            // Reset counts for the next iteration
            redCount = 0;
            greenCount = 0;
            blueCount = 0;

            // Reset the sample count
            sampleCount = 0;
            
            
        }
    } while (!(dominantColor == "Blue" || dominantColor == "Green" || dominantColor == "Red"));
    return dominantColor;
    
}



/*
code 2 work this

#include "color_sensor.h"

ColorSensor::ColorSensor() {
  redFrequency = 0;
  greenFrequency = 0;
  blueFrequency = 0;
}

void ColorSensor::setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Setting frequency-scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  Serial.begin(9600);
}

void ColorSensor::loop() {
  for (int i = 0; i < 1000; i++) {
    // Setting red filtered photodiodes to be read
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);
    // Reading the output frequency
    redFrequency += pulseIn(sensorOut, LOW);
    delay(1);

    // Setting Green filtered photodiodes to be read
    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);
    // Reading the output frequency
    greenFrequency += pulseIn(sensorOut, LOW);
    delay(1);

    // Setting Blue filtered photodiodes to be read
    digitalWrite(S2, LOW);
    digitalWrite(S3, HIGH);
    // Reading the output frequency
    blueFrequency += pulseIn(sensorOut, LOW);
    delay(1);
  }

  // Printing the average frequencies on the serial monitor
  Serial.print("R= "); //printing name
  Serial.print(redFrequency / 1000); //printing average RED color frequency
  Serial.print("  ");

  Serial.print("G= "); //printing name
  Serial.print(greenFrequency / 1000); //printing average GREEN color frequency
  Serial.print("  ");

  Serial.print("B= "); //printing name
  Serial.print(blueFrequency / 1000); //printing average BLUE color frequency
  Serial.println("  ");

  // Determine dominant color
  if (redFrequency > greenFrequency && redFrequency > blueFrequency) {
    dominantColor = 'R';
  } else if (greenFrequency > redFrequency && greenFrequency > blueFrequency) {
    dominantColor = 'G';
  } else if (blueFrequency > redFrequency && blueFrequency > greenFrequency) {
    dominantColor = 'B';
  } else {
    dominantColor = 'U'; // Unknown color
  }
  Serial.print("Dominant Color: ");
  Serial.println(dominantColor);

  // Reset frequencies for next iteration
  redFrequency = 0;
  greenFrequency = 0;
  blueFrequency = 0;
}
*/
