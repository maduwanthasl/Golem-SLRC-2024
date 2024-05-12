#include "read_sensor_values.h"


void read_sensor_values()
{
  readThresholdFromEEPROM();
  //White == 1 & Black == 0 left - , right +
  for (int sensorIndex = 0; sensorIndex < numSensors; sensorIndex++) {
    sensorValues[sensorIndex] = analogRead(sensorPins[sensorIndex]);
    if (sensorValues[sensorIndex] > threshold[sensorIndex]) {
        sensorValues[sensorIndex] = 0;
    } else {
        sensorValues[sensorIndex] = 1;
    }
  }

  // //print the values or the sensorVales array
  // for (int i = 0; i < numSensors; i++) {
  //   Serial.print(sensorValues[i]);
  //   Serial.print(" ");
  // }
  // Serial.println("");

  

  // Define all expected values in a single array
  int expectedValues[][numSensors] = {
    {0, 0, 0, 0, -1, -1, -1, -1, 0, 0, 0, 0},
    {0, 0, 0, 1, -1, -1, -1, -1, 1, 0, 0, 0},
    {0, 0, 0, 1, -1, -1, -1, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, -1, -1, -1, 1, 0, 0, 0},
    {0, 0, 0, 1, -1, -1, 1, 0, 0, 0, 0, 0},
    {0, 0, 1, -1, -1, -1, -1, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, -1, -1, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, -1, -1, -1, -1, 1, 0, 0},
    {0, 0, 1, -1, -1, -1, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, -1, -1, -1, 1, 0, 0},
    {0 ,0 ,0 ,0 ,0 ,0 ,1 ,-1 ,-1 ,-1 ,1 ,0 },
    {0 ,1 ,-1 ,-1 ,-1 ,1 ,0 ,0 ,0 ,0 ,0 ,0 },
    {0, 0, 1, -1, -1, 1, 0, 0, 0, 0, 0, 0},
    {0, 1, -1, -1, -1, -1, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, -1, -1, 1, 0, 0},
    {0, 0, 0, 0, 0, 1, -1, -1, -1, -1, 1, 0},
    {0, 1, -1, -1, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 1, -1, -1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, -1, 1, 0},
    {0, 1, -1, 1, 0, 0, 0, 0, 0, 0, 0, 0},  
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  
    {0, -1, 1, -1, -1, -1, -1, -1, -1, 1, -1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, -1, -1, 1, -1},
    {-1, 1,-1, -1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, 1},
    {1, -1,-1, -1, 0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //aall black
    {1, -1, -1, -1, 1, 0, 0, 0, 0, 0, 0, 0},
    {1, -1, -1, -1, -1, 1, 0, 0, 0, 0, 0, 0},
    {1, -1, -1, -1, -1, -1, 1, 0, 0, 0, 0, 0},
    {1, -1, -1, -1, -1, -1, -1, 1, 0, 0, 0, 0},
    {1, -1, -1, -1, -1, -1, -1, 1, 1, 0, 0, 0},
    {1, -1, -1, -1, -1, -1, -1, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 1, -1, -1, -1, 1},
    {0, 0, 0, 0, 0, 0, 1, -1, -1, -1, -1, 1},
    {0, 0, 0, 0, 0, 1, -1, -1, -1, -1, -1, 1},
    {0, 0, 0, 0, 1, -1, -1, -1, -1, -1, -1, 1},
    {0, 0, 0, 1, 1, -1, -1, -1, -1, -1, -1, 1},
    {0, 0, 1, 1, 1, -1, -1, -1, -1, -1, -1, 1},
    {0, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    
  };


  // Define corresponding error values
  int errorValues[] = {0, 0,-1, 1, -2, -2, 2, 2, -3, +3,4,-4, -4, -4,4,4, -5,5,6,-6,140,150,-160,160,-160,160,103,100,100,100,100,100,100,101,101,101,101,101,101,102,104};

  // Initialize conditionMet as false
  bool conditionMet = false;

  int defaultErrorValue = 0;
  

  // Check if any condition is met
  for (int condIndex = 0; condIndex < sizeof(expectedValues) / sizeof(expectedValues[0]); condIndex++) {
    conditionMet = true; // Assume the condition is met initially
    for (int sensorIndex = 0; sensorIndex < numSensors; sensorIndex++) {
      if (expectedValues[condIndex][sensorIndex] != -1 && sensorValues[sensorIndex] != expectedValues[condIndex][sensorIndex]) {
        conditionMet = false; // Condition not met, break the inner loop
        break;
      }
    }
    if (conditionMet) {
            error = errorValues[condIndex]; // Set error based on the condition
            if (condIndex >= sizeof(errorValues) / sizeof(errorValues[0]) - 13) {
              motor_pos = 0;  motor_pos2 =0;
              count_encoder(0.45);
              // analogWrite(leftmotor_pwm, 50); //Left Motor Speed
              // analogWrite(rightmotor_pwm, 66); //Right Motor Speed
              // forward();
              // delay(300);
              junction_count++; // Increment junction_met if the last 10 values are met
              motor_pos = 0;  motor_pos2 =0;
              Serial.println(junction_count);
            }
            break; // Exit the loop if condition is met
        }
  }

  // If no condition is met, set error to default value
  if (!conditionMet) {
    error = defaultErrorValue;
  }

  // Serial.print("    ");
  // Serial.print(error);
  // Serial.println();
  // delay(1000);
}
