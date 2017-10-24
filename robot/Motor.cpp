//
// Created by Viktor Hundahl Strate on 13/10/2017.
//

#include <Arduino.h>
#include "Motor.h"
#include "Debug.h"

Motor::Motor() = default;

void resetMotors() {
    analogWrite(MOTOR_SPEED_LEFT, 0);
    analogWrite(MOTOR_SPEED_RIGHT, 0);

    digitalWrite(MOTOR_LEFT_BACKWARDS, LOW);
    digitalWrite(MOTOR_LEFT_FORWARD, LOW);

    digitalWrite(MOTOR_RIGHT_BACKWARDS, LOW);
    digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
}

void Motor::forward(uint8_t speed) {
#ifdef DISABLE_MOTOR
    resetMotors();

    analogWrite(MOTOR_SPEED_LEFT, speed);
    analogWrite(MOTOR_SPEED_RIGHT, speed);

    digitalWrite(MOTOR_LEFT_FORWARD, HIGH);
    digitalWrite(MOTOR_RIGHT_FORWARD, HIGH);
#endif
}

void Motor::backwards(uint8_t speed) {
#ifdef DISABLE_MOTOR
    resetMotors();

    analogWrite(MOTOR_SPEED_LEFT, speed);
    analogWrite(MOTOR_SPEED_RIGHT, speed);

    digitalWrite(MOTOR_LEFT_BACKWARDS, HIGH);
    digitalWrite(MOTOR_RIGHT_BACKWARDS, HIGH);
#endif
}

void Motor::right(uint8_t speed, uint8_t turnRate) {
#ifdef DISABLE_MOTOR
    resetMotors();

    debugLog("Turn right, turnRate=" + String(turnRate) + ", calculatedSpeed=" + String(speed - (turnRate * speed)/255.0));

    analogWrite(MOTOR_SPEED_RIGHT, speed - (turnRate * speed)/255.0);
    analogWrite(MOTOR_SPEED_LEFT, speed);

    digitalWrite(MOTOR_LEFT_FORWARD, HIGH);
    digitalWrite(MOTOR_RIGHT_FORWARD, HIGH);
#endif
}

void Motor::left(uint8_t speed, uint8_t turnRate) {
#ifdef DISABLE_MOTOR
    resetMotors();

    debugLog("Turn left, turnRate=" + String(turnRate) + ", calculatedSpeed=" + String(speed - (turnRate * speed)/255.0) );

    analogWrite(MOTOR_SPEED_LEFT, speed - (turnRate * speed)/255.0);
    analogWrite(MOTOR_SPEED_RIGHT, speed);

    digitalWrite(MOTOR_LEFT_FORWARD, HIGH);
    digitalWrite(MOTOR_RIGHT_FORWARD, HIGH);
#endif
}

void Motor::degreeTurn(uint8_t speed, unsigned int degrees) {
#ifdef DISABLE_MOTOR
    debugLog("Degree turn, speed=" + String(speed) + ", degree=" + String(degrees));
    if (degrees < 90) {
        // move right
        uint8_t turnRate = map(degrees, 90, 180, 0, 255);
        right(speed, turnRate);
    } else if (degrees < 90) {
        // move left

        uint8_t turnRate = map(degrees, 90, 0, 0, 255);
        left(speed, turnRate);
    } else {
        // move forwards
        forward(speed);
    }
#endif
}

void Motor::tankTurn(uint8_t speed, boolean rightDirection) {
#ifdef DISABLE_MOTOR
    resetMotors();

    digitalWrite(MOTOR_RIGHT_FORWARD, !rightDirection ? HIGH : LOW);
    digitalWrite(MOTOR_RIGHT_BACKWARDS, rightDirection ? HIGH : LOW);

    digitalWrite(MOTOR_LEFT_FORWARD, rightDirection ? HIGH : LOW);
    digitalWrite(MOTOR_LEFT_BACKWARDS, !rightDirection ? HIGH : LOW);

    analogWrite(MOTOR_SPEED_LEFT, speed);
    analogWrite(MOTOR_SPEED_RIGHT, speed);
#endif
}

uint8_t Motor::easeOut(uint8_t position) {
    return (uint8_t) (1 - pow((1-position/255.0), 5)) * 255;
}
