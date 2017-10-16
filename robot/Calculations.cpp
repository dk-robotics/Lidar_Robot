#include <Arduino.h>
#include "Calculations.h"

Calculations::Calculations()
        : distances(), step(0), servoDirection(true) {
    servo.attach(SERVO_PIN);
    lidar.begin();
}

void Calculations::loop() {
    moveServo();
    this->step += servoDirection ? 1 : -1;

    getDistance();
//    distances[this->step] = lidar.getDistance();
//    Serial.println("Step value" + String(step));
    /*getDistance();
	for(int i = 0; i < MEASURE_POINTS; i++)
		Serial.println(distances[i]);*/
    calculateMoveDirection();

    // Delay before next servo move
    delay(20);
}

void Calculations::calculateMoveDirection() {
    float longestDistance = 0;
    unsigned int distanceIndex = 0;

    for (unsigned int i = 0; i < MEASURE_POINTS; i++) {
        if (distances[i] > longestDistance) {
            longestDistance = distances[i];
            distanceIndex = i;
        }
    }

    //motor.degreeTurn(60, distanceIndex*180 / ((float)MEASURE_POINTS));
    motor.degreeTurn(60, 180);
    //motor.forward(127);
}

void Calculations::moveServo() {
    // Change direction of servo if max/min position is reached
    if ((this->step+1) * 180 / MEASURE_POINTS >= 180) {
        servoDirection = false;
    } else if ((this->step-1) <= 0) {
        servoDirection = true;
    }

    // Update servo position
    servo.write(this->step * 180 / MEASURE_POINTS);
}

void Calculations::getDistance() {
    distances[this->step] = lidar.getDistance();
}
