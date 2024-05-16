#ifndef TCA9548A_H
#define TCA9548A_H

#include "Wire.h"
extern "C" { 
#include "utility/twi.h"  // from Wire library, so we can do bus scanning
}
#include "measure_distance_tof.h"
#include "color_sensor.h"
#include "variables.h"
#include "gyro.h"
#include "oled_display.h"

#define TCAADDR 0x70



void TCA9548A(uint8_t i);
void tca9548a_setup();
void TCA9548A_tof_sensor(int a, int b);
String TCA9548A_color_sensor(int a);
void TCA9548A_gyro(int a,int b);
void TCA9548A_display(int a);
float TCA9548A_gyro_loop(int a);


#endif