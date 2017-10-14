#include <Arduino.h>
#include "Calculations.h"

Calculations::Calculations()
        : distances(), servoStep(0), servoDirection(true) {
    servo.attach(SERVO_PIN);
}

void Calculations::loop() {
    // TODO implement this
    // lidar.getDistance()
    moveServo();

    calculateMoveDirection();
}

void Calculations::moveServo() {
    if (servoStep * 180 / MEASURE_POINTS >= 180) {
        servoDirection = false;
    } else if (servoStep <= 0) {
        servoDirection = true;
    }

    if (servoDirection) {
        servoStep += MEASURE_POINTS;
    } else {
        servoStep -= MEASURE_POINTS;
    }

    servo.write(servoStep * 180 / MEASURE_POINTS);
}

void Calculations::calculateMoveDirection() {
    float shortestDistance = 0xffff;
    // if no distance was found move forwards
    unsigned int distanceIndex = MEASURE_POINTS / 2;

    for (unsigned int i = 0; i < MEASURE_POINTS; i++) {
        if (distances[i] < shortestDistance) {
            shortestDistance = distances[i];
            distanceIndex = i;
        }
    }

    motor.degreeTurn(127, (distanceIndex * 180) / MEASURE_POINTS);
}
