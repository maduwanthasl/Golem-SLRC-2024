#ifndef MEASURE_DISTANCE_TOF_H
#define MEASURE_DISTANCE_TOF_H

#include <Arduino.h>
#include "line_follow.h"
#include "Adafruit_VL53L0X.h"
#include "measure_distance_tof.h"

void measure_distance_tof_setup();
void measure_distance_tof_loop(int numSamples);


#endif
