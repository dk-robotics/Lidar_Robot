//
// Created by Viktor Hundahl Strate on 13/10/2017.
//

#include <Arduino.h>
#include "Motor.h"
#include "Debug.h"

Motor::Motor() = default;

uint8_t easeOut(uint8_t position) {
    return (uint8_t) (1 - pow((1-position/255.0), 5)) * 255;
}

void resetMotors() {
    analogWrite(MOTOR_SPEED_LEFT, 0);
    analogWrite(MOTOR_SPEED_RIGHT, 0);

    digitalWrite(MOTOR_LEFT_BACKWARDS, LOW);
    digitalWrite(MOTOR_LEFT_FORWARD, LOW);

    digitalWrite(MOTOR_RIGHT_BACKWARDS, LOW);
    digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
}

uint8_t calculateTurnRate(uint8_t speed, uint8_t turnRate, bool boost) {
    int value;
    if (boost) {
        value = (int) (speed + turnRate * speed / 255.0);
    } else {
        value = (int) (speed - turnRate * speed / 255.0);
    }
    debugLog("Calculating turn rate: " + String(value) + ", speed: " + String(speed) + " input turn rate: " + turnRate);
    if (value > 255) {
        return 255;
    } else if (value < 0) {
        return 0;
    } else {
        return (uint8_t) value;
    }
}

void Motor::forward(uint8_t speed) {
#ifndef DISABLE_MOTOR
    resetMotors();

    analogWrite(MOTOR_SPEED_LEFT, speed);
    analogWrite(MOTOR_SPEED_RIGHT, speed);

    digitalWrite(MOTOR_LEFT_FORWARD, HIGH);
    digitalWrite(MOTOR_RIGHT_FORWARD, HIGH);
#endif
}

void Motor::backwards(uint8_t speed) {
#ifndef DISABLE_MOTOR
    resetMotors();

    analogWrite(MOTOR_SPEED_LEFT, speed);
    analogWrite(MOTOR_SPEED_RIGHT, speed);

    digitalWrite(MOTOR_LEFT_BACKWARDS, HIGH);
    digitalWrite(MOTOR_RIGHT_BACKWARDS, HIGH);
#endif
}

void Motor::right(uint8_t speed, uint8_t turnRate) {
    debugLog("Moving motors left=" + String(calculateTurnRate(speed, turnRate, true)) + " right="
             + String(calculateTurnRate(speed, turnRate, false)));
#ifndef DISABLE_MOTOR
    resetMotors();

    analogWrite(MOTOR_SPEED_RIGHT, calculateTurnRate(speed, turnRate, false));
    //analogWrite(MOTOR_SPEED_RIGHT, 0);
    analogWrite(MOTOR_SPEED_LEFT, calculateTurnRate(speed, turnRate, true));

    digitalWrite(MOTOR_LEFT_FORWARD, HIGH);
    digitalWrite(MOTOR_RIGHT_FORWARD, HIGH);
#endif
}

void Motor::left(uint8_t speed, uint8_t turnRate) {
    debugLog("Moving motors left=" + String(calculateTurnRate(speed, turnRate, false)) + " right="
             + String(calculateTurnRate(speed, turnRate, true)));

#ifndef DISABLE_MOTOR
    resetMotors();

    analogWrite(MOTOR_SPEED_LEFT, calculateTurnRate(speed, turnRate, false));
    //analogWrite(MOTOR_SPEED_LEFT, 0);
    analogWrite(MOTOR_SPEED_RIGHT, calculateTurnRate(speed, turnRate, true));

    digitalWrite(MOTOR_LEFT_FORWARD, HIGH);
    digitalWrite(MOTOR_RIGHT_FORWARD, HIGH);
#endif
}

void Motor::degreeTurn(uint8_t speed, unsigned int degrees) {
    debugLog("Degree turn, speed=" + String(speed) + ", degree=" + String(degrees));
    if (degrees < 90) {
        // move right
        uint8_t turnRate = map(degrees, 90, 0, 0, 255);
        debugLog("Mapped turn rate, right " + String(turnRate));
        right(speed, turnRate);
    } else if (degrees > 90) {
        // move left

        uint8_t turnRate = map(degrees, 90, 180, 0, 255);
        debugLog("Mapped turn rate, left " + String(turnRate));
        left(speed, turnRate);
    } else {
        // move forwards
        forward(speed);
    }
}

void Motor::tankTurn(uint8_t speed, boolean rightDirection) {
#ifndef DISABLE_MOTOR
    resetMotors();

    digitalWrite(MOTOR_RIGHT_FORWARD, !rightDirection ? HIGH : LOW);
    digitalWrite(MOTOR_RIGHT_BACKWARDS, rightDirection ? HIGH : LOW);

    digitalWrite(MOTOR_LEFT_FORWARD, rightDirection ? HIGH : LOW);
    digitalWrite(MOTOR_LEFT_BACKWARDS, !rightDirection ? HIGH : LOW);

    analogWrite(MOTOR_SPEED_LEFT, speed);
    analogWrite(MOTOR_SPEED_RIGHT, speed);
#endif
}
