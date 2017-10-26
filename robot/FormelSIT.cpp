#include <Arduino.h>
#include "FormelSIT.h"
#include "Debug.h"

FormelSIT::FormelSIT()
        : distances(), step(0), stepperDirection(true), longestDistanceIndex(0) {}

void FormelSIT::start() {
    debugLog("Starting formel SIT");
    lidar.begin();
    stepper.calibrate();
}

void FormelSIT::loop() {

    //while(digitalRead(2) == LOW) {
    //    delay(15);
    //}

    debugLog("");
    debugLog("------ NEXT LOOP CYCLE ------");
    // Change direction of servo if max/min position is reached
    if ((this->step + 1) * 180.0f / MEASURE_POINTS >= 180) {
        stepperDirection = false;
    } else if ((this->step - 1) <= 0) {
        stepperDirection = true;
    }

    //stepper.sweep();
    debugLog("Moving stepper " + (stepperDirection ? String("right ") : String("left ")) +
             String((STEPS_PER_REV) / (2 * MEASURE_POINTS)) + " steps");
    stepper.move((STEPS_PER_REV) / (2 * MEASURE_POINTS), stepperDirection);

    getDistance();

    calculateMoveDirection();

    this->step += stepperDirection ? 1 : -1;
}

void FormelSIT::calculateMoveDirection() {
    //float multiplier = ( (1 - abs((MEASURE_POINTS-1)/2 - step)) / 4 ) + 1;
    if (distances[this->step] < 40 && distances[this->step] > 5) {
        debugLog("Found minimum distance");

        if (minDistanceStuckPrevious && millis() - minDistanceStuckTime > 3000) {
            debugLog("Stuck too long, trying to get free");
            motor.backwards(45);
            delay(1000);
            motor.tankTurn(45, false);
            delay(1500);
        }

        motor.tankTurn(50, step < MEASURE_POINTS / 2);
        if (!minDistanceStuckPrevious) {
            minDistanceStuckPrevious = true;
            minDistanceStuckTime = millis();
        }

        return;
    } else {
        minDistanceStuckPrevious = false;
    }

    debugLog("Calculating move direction");
    if (distances[this->step] > distances[longestDistanceIndex]) {
        longestDistanceIndex = this->step;
        debugLog("Found new longest distance, " + String(longestDistanceIndex));

        debugLog("Calling degree turn from FormelSIT");
        motor.degreeTurn(50, longestDistanceIndex * 180 / ((float) MEASURE_POINTS - 1));
#ifdef DEBUG_LIDAR
        for (unsigned int i = 0; i < MEASURE_POINTS; i++) {
            if (i == longestDistanceIndex) {
                Serial.print("*");
            } else {
                Serial.print("-");
            }
        }
        Serial.println("   " + String(distances[longestDistanceIndex]));
#endif
    } else if (this->step == longestDistanceIndex) {
        debugLog("Did not find new distance, must check whole array");
        float newLongestDistance = 0;

        for (unsigned int i = 0; i < MEASURE_POINTS; i++) {
            if (distances[i] > newLongestDistance) {
                newLongestDistance = distances[i];
                longestDistanceIndex = i;
            }
        }
    }
}

void FormelSIT::getDistance() {
    debugLog("Getting distance from lidar");
    distances[this->step] = lidar.getDistance();
}
