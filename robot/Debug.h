//
// Created by Viktor Hundahl Strate on 23/10/2017.
//

#ifndef LIDARROBOT_DEBUG_H
#define LIDARROBOT_DEBUG_H

// Prints general debug information to the console
//#define DEBUG

// Prints lidar results to the console
//#define DEBUG_LIDAR

// Disables the motors for testing
//#define DISABLE_MOTOR

#ifdef DEBUG
    #define debugLog(X) Serial.println(X)
#else
    #define debugLog(X)
#endif

#endif //LIDARROBOT_DEBUG_H
