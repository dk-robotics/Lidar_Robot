#include <Arduino.h>
#include "Calculations.h"

Calculations::Calculations()
        : distances(), step(0), servoDirection(true) {
    servo.attach(SERVO_PIN);
    lidar.begin();
}

void Calculations::loop() {
    Serial.print("Loop starting");
    this->step += servoDirection ? 1 : -1;
    moveServo();

    getDistance();
    calculateMoveDirection();

    // Delay before next servo move
    delay(1);
}

void Calculations::calculateMoveDirection() {
    float shortestDistance = 0xffffff;
    unsigned int distanceIndex = 0;

    for (unsigned int i = 0; i < MEASURE_POINTS; i++) {
        if (distances[i] < shortestDistance) {
            shortestDistance = distances[i];
            distanceIndex = i;
        }
    }

    motor.degreeTurn(127, (distanceIndex * 180) / MEASURE_POINTS);
}

void Calculations::moveServo() {
    Serial.print("Moving servo");
    // Change direction of servo if max/min position is reached
    if (this->step * 180 / MEASURE_POINTS >= 180) {
        servoDirection = false;
    } else if (this->step <= 0) {
        servoDirection = true;
    }

    // Update servo position
    Serial.print(String("Servo value") + (this->step * 180 / MEASURE_POINTS));
    servo.write(this->step * 180 / MEASURE_POINTS);
}

void Calculations::getDistance() {
    distances[this->step] = lidar.getDistance();
}
