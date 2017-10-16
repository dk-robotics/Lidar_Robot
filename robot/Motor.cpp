//
// Created by Viktor Hundahl Strate on 13/10/2017.
//

#include <Arduino.h>
#include "Motor.h"

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
    resetMotors();

    analogWrite(MOTOR_SPEED_LEFT, speed);
    analogWrite(MOTOR_SPEED_RIGHT, speed);

    digitalWrite(MOTOR_LEFT_FORWARD, HIGH);
    digitalWrite(MOTOR_RIGHT_FORWARD, HIGH);
}

void Motor::backwards(uint8_t speed) {
    resetMotors();

    analogWrite(MOTOR_SPEED_LEFT, speed);
    analogWrite(MOTOR_SPEED_RIGHT, speed);

    digitalWrite(MOTOR_LEFT_BACKWARDS, HIGH);
    digitalWrite(MOTOR_RIGHT_BACKWARDS, HIGH);
}

void Motor::right(uint8_t speed, uint8_t turnRate) {
    resetMotors();

    analogWrite(MOTOR_SPEED_RIGHT, speed);
    analogWrite(MOTOR_SPEED_LEFT, (speed - (turnRate * speed)/0xff));

    digitalWrite(MOTOR_LEFT_FORWARD, HIGH);
    digitalWrite(MOTOR_RIGHT_FORWARD, HIGH);
}

void Motor::left(uint8_t speed, uint8_t turnRate) {
    resetMotors();

    analogWrite(MOTOR_SPEED_LEFT, speed);
    analogWrite(MOTOR_SPEED_RIGHT, (speed - (turnRate * speed)/0xff));

    digitalWrite(MOTOR_LEFT_FORWARD, HIGH);
    digitalWrite(MOTOR_RIGHT_FORWARD, HIGH);
}

void Motor::degreeTurn(uint8_t speed, unsigned int degrees) {
    if (degrees > 90) {
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
}
