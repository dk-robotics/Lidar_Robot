#include <Arduino.h>
#include "FormelSIT.h"
#include "Debug.h"

FormelSIT::FormelSIT()
        : distances(), step(0), servoDirection(true), longestDistanceIndex(0) {}

void FormelSIT::start() {
    servo.attach(SERVO_PIN);
    lidar.begin();
}

void FormelSIT::loop() {
    moveServo();

    // Change direction of servo if max/min position is reached
    if ((this->step+1) * 180.0f / MEASURE_POINTS >= 180) {
        servoDirection = false;
    } else if ((this->step-1) <= 0) {
        servoDirection = true;
    }



    // Delay before next servo move
    delay(20);

    getDistance();

    calculateMoveDirection();

    this->step += servoDirection ? 1 : -1;
}

void FormelSIT::calculateMoveDirection() {

/*
    float longestDistance = 0;
    unsigned int longestDistanceIndex = 0;

    for (unsigned int i = 0; i < MEASURE_POINTS; i++) {
        if (distances[i] > longestDistance) {
            longestDistance = distances[i];
            longestDistanceIndex = i;
            Serial.print(",*" + String(distances[i]));
        } else {
            Serial.print(", " + String(distances[i]));
        }
    }
*/



    if(distances[this->step] > distances[longestDistanceIndex]){
        longestDistanceIndex = this->step;
        debugLog("Found new longest distance, " + String(longestDistanceIndex));
    } else if (this->step == longestDistanceIndex) {
        float newLongestDistance = 0;

        for (unsigned int i = 0; i < MEASURE_POINTS; i++) {
            if (distances[i] > newLongestDistance) {
                newLongestDistance = distances[i];
                longestDistanceIndex = i;
            }
        }
    }

    motor.degreeTurn(5, longestDistanceIndex*180 / ((float)MEASURE_POINTS));
    //motor.degreeTurn(20, 180);
    //motor.forward(127);

}

void FormelSIT::moveServo() {
    // Update servo position
    servo.write(this->step * 180 / MEASURE_POINTS);
}

void FormelSIT::getDistance() {
    distances[this->step] = lidar.getDistance();
}
