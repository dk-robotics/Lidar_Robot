#ifndef Calculations_h
#define Calculations_h

#include <Arduino.h>
#include <Servo.h>
#include "Lidar.h"
#include "Motor.h"

#define MEASURE_POINTS 24

class Calculations {
public:
    Calculations();
    void loop();

private:
    void moveServo();
    void calculateMoveDirection();
    void getDistance();

    Lidar lidar;
    Motor motor;


    int distances[MEASURE_POINTS];
    Servo servo;
    int step;
    // true = right, false = left
    boolean servoDirection;
};

#endif

