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

void setup() {
#if defined(DEBUG) || defined(DEBUG_LIDAR)
    Serial.begin(9600);
    debugLog("Robot starting...");
#endif

    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);

    stateManager.start();
}

void loop() {
    stateManager.loop();
}

#endif //LIDARROBOT_MAIN_H
