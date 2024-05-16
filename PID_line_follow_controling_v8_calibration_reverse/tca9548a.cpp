#include <Arduino.h>
#include "tca9548a.h"
ColorSensor colorSensor; // Create an instance of the ColorSensor class



void TCA9548A(uint8_t i) 
{
  if (i > 7) return;
 
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}

void tca9548a_setup()
{
  Serial.begin(9600);

  while (!Serial);
  delay(1000);
  Wire.begin();

  Serial.print("Start.");

  TCA9548A(4);
  setupDisplay(); // Call the setup function of the MeasureDistanceTOF object
  TCA9548A(tof_front);
  measure_distance_tof_setup(); // Call the setup function of the MeasureDistanceTOF object
  TCA9548A(color_front);
  colorSensor.setup(); // Call the setup function of the ColorSensor instance
  TCA9548A(color_down_left);
  colorSensor.setup(); // Call the setup function of the ColorSensor instance
  TCA9548A(color_down_right);
  colorSensor.setup(); // Call the setup function of the ColorSensor instance
  TCA9548A(gyro);
  gyro_setup(); // Call the setup function of the ColorSensor instance



}

void TCA9548A_tof_sensor(int a, int b){
  TCA9548A(a);
  measure_distance_tof_loop(b);
}

String TCA9548A_color_sensor(int a) {
    TCA9548A(a);
    colorSensor.loop();
    String color = dominantColor;
    Serial.print("color   ");
    Serial.print(dominantColor);
    Serial.println("  ");
    return color;
}


void TCA9548A_gyro(int a,int b){
  TCA9548A(a);
  sharp_turns(b);
}

float TCA9548A_gyro_loop(int a){
  TCA9548A(a);
  gyro_loop();
}

void TCA9548A_display(int a){
  TCA9548A(a);
  loopDisplay();
}
