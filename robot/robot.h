/**
 * This is the main entry file, and is either called by robot.cpp, or robot.ino
 * depending on whether CMake or Arduino IDE, respectively, was used to build the project
 */

#ifndef LIDARROBOT_MAIN_H
#define LIDARROBOT_MAIN_H

#include "Calculations.h"

Calculations calcs;

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
}

void loop() {
    // put your main code here, to run repeatedly:
    calcs.loop();
}

#endif //LIDARROBOT_MAIN_H
