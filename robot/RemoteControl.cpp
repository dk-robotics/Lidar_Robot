//
// Created by Viktor Hundahl Strate on 20/11/2017.
//

#include <Arduino.h>
#include "RemoteControl.h"

#define INPUT_TIMEOUT 50000

void RemoteControl::start() {
    pinMode(RC_LEFT_RIGHT, INPUT);
    pinMode(RC_LEFT_UP, INPUT);
    pinMode(RC_RIGHT_RIGHT, INPUT);
    pinMode(RC_RIGHT_UP, INPUT);
}

void RemoteControl::loop() {
    unsigned long forwards = pulseIn(RC_LEFT_UP, HIGH, INPUT_TIMEOUT);
    unsigned long sideways = pulseIn(RC_RIGHT_RIGHT, HIGH, INPUT_TIMEOUT);
    unsigned long backwards = pulseIn(RC_RIGHT_UP, HIGH, INPUT_TIMEOUT);

    if (forwards | sideways | backwards == 0) return;
    if (sideways == 0) sideways = 1500;

    if (backwards < 1400 && forwards < 1400 && abs(1500-sideways) < 200)
        motor.backwards(map(backwards, 1400, 1000, 0, 255));
    else
        motor.degreeTurn(max(map(forwards, 1070, 1981, 0, 255), 0), map(sideways, 2000, 1000, 0, 180));
}
