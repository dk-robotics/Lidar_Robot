#ifndef Calculations_h
#define Calculations_h

#include <Arduino.h>
#include "Lidar.h"

#define MEASURE_POINTS 12

class Calculations {
public:
    Calculations();
    void loop();

private:
    Lidar lidar;
    float distances[MEASURE_POINTS];
};

#endif

