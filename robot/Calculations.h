#ifndef Calculations_h
#define Calculations_h

#include <Arduino.h>
#include <Servo.h>
#include "Lidar.h"
#include "Motor.h"

#define MEASURE_POINTS 12

class Calculations {
public:
    Calculations();
    void loop();

private:
    void moveServo();
    void calculateMoveDirection();

    Lidar lidar;
    Motor motor;


    float distances[MEASURE_POINTS];
    Servo servo;
    int servoStep;
    // true = right, false = left
    boolean servoDirection;
};

#endif

