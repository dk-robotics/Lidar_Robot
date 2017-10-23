/**
 * This is the main entry file, and is either called by robot.cpp, or robot.ino
 * depending on whether CMake or Arduino IDE, respectively, was used to build the project
 */

#ifndef LIDARROBOT_MAIN_H
#define LIDARROBOT_MAIN_H

#include "FormelSIT.h"
#include "StateManager.h"
#include "Debug.h"

StateManager stateManager;
Motor motor;

void setup() {
    Serial.begin(9600);
    debugLog("Robot starting...");

    stateManager.start();
}

void loop() {
    stateManager.loop();
}

#endif //LIDARROBOT_MAIN_H
