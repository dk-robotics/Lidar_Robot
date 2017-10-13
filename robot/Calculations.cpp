#include <Arduino.h>
#include "Calculations.h"

Calculations::Calculations() = default;

void Calculations::loop() {
    // TODO implement this
    // lidar.getDistance()

    float shortestDistance = 0xffff;
    int distanceIndex;

    for (int i = 0; i < MEASURE_POINTS; i++) {
        if (distances[i] < shortestDistance) {
            shortestDistance = distances[i];
            distanceIndex = i;
        }
    }
}
