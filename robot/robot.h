/**
 * This is the main entry file, and is either called by robot.cpp, or robot.ino
 * depending on whether CMake or Arduino IDE, respectively, was used to build the project
 */

#ifndef LIDARROBOT_MAIN_H
#define LIDARROBOT_MAIN_H

#include "RemoteControl.h"
#include "Debug.h"

RemoteControl rc;

void setup() {
#if defined(DEBUG) || defined(DEBUG_LIDAR)
    Serial.begin(9600);
    debugLog("Robot starting...");
#endif
    rc.start();
}

void loop() {
    rc.loop();
}

#endif //LIDARROBOT_MAIN_H
