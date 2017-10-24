//
// Created by Viktor Hundahl Strate on 14/10/2017.
//

#ifndef LIDARROBOT_PINSETUP_H
#define LIDARROBOT_PINSETUP_H

#include <Arduino.h>

// Motor pins
#define MOTOR_RIGHT_FORWARD 8
#define MOTOR_RIGHT_BACKWARDS 7

#define MOTOR_LEFT_FORWARD 9
#define MOTOR_LEFT_BACKWARDS 4

#define MOTOR_SPEED_RIGHT 6
#define MOTOR_SPEED_LEFT 5

// Stepper
#define STEPPER_DIRECTION 10
#define STEPPER_STEP 11
#define HALL_SENSOR 12

// Lidar
#define SDA A4
#define SCL A5

#endif //LIDARROBOT_PINSETUP_H
