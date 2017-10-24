#ifndef Calculations_h
#define Calculations_h

#include <Arduino.h>
#include <Servo.h>
#include "Lidar.h"
#include "Motor.h"
#include "ArduinoLoopable.h"

#define MEASURE_POINTS 8

class FormelSIT : public ArduinoLoopable {
public:
    FormelSIT();

private:
public:
    void start() override;

    void loop() override;

private:
    void moveServo();
    void calculateMoveDirection();
    void getDistance();

    Lidar lidar;
    Motor motor;


    int distances[MEASURE_POINTS];
    int longestDistanceIndex;
    Servo servo;
    int step;
    // true = right, false = left
    boolean servoDirection;
};

#endif

