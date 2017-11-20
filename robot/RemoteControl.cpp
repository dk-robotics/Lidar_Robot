//
// Created by Viktor Hundahl Strate on 20/11/2017.
//

#include <Arduino.h>
#include "RemoteControl.h"
#include "PinSetup.h"
#include "Debug.h"

void RemoteControl::start() {
    pinMode(RC_LEFT_RIGHT, INPUT);
    pinMode(RC_LEFT_UP, INPUT);
    pinMode(RC_RIGHT_RIGHT, INPUT);
    pinMode(RC_RIGHT_UP, INPUT);
}

void RemoteControl::loop() {
    unsigned long forwards = pulseIn(RC_LEFT_UP, HIGH);
    unsigned long sideways = pulseIn(RC_RIGHT_RIGHT, HIGH);

    if (forwards < 1200 && abs(1500-sideways) < 200) {
        unsigned long backwards = pulseIn(RC_RIGHT_UP, HIGH);
        if (backwards < 1400) {
            motor.backwards(map(backwards, 1400, 1000, 0, 255));
        } else {
            motor.degreeTurn(max(map(forwards, 1070, 1981, 0, 255), 0), map(sideways, 2000, 1000, 0, 180));
        }
    } else {
        motor.degreeTurn(max(map(forwards, 1070, 1981, 0, 255), 0), map(sideways, 2000, 1000, 0, 180));
    }
}
