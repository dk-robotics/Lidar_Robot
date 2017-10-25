#ifndef Calculations_h
#define Calculations_h

#include <Arduino.h>
#include <Servo.h>
#include "Lidar.h"
#include "Motor.h"
#include "ArduinoLoopable.h"
#include "Stepper.h"

#define MEASURE_POINTS 10

class FormelSIT : public ArduinoLoopable {
public:
    FormelSIT();

private:
public:
    void start() override;

    void loop() override;

private:
    void calculateMoveDirection();
    void getDistance();

    Lidar lidar;
    Motor motor;

    int distances[MEASURE_POINTS];
    int longestDistanceIndex;
    Stepper stepper;
    int step;

    // true = right, false = left
    boolean stepperDirection;
};

#endif

