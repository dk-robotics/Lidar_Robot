#ifndef Stepper_h
#define Stepper_h

#include <Arduino.h>
#include "PinSetup.h"

#define STEPS_PER_REV 200
#define STEPPER_WAIT_TIME 2

class Stepper {
public:
    Stepper();

    /**
     * Resets the motor to face straight forward
     * Used to get a known starting position
     *
     * NOTE: Blocks the thread
     */
    void calibrate();

    /**
     * Moves the stepper motor
     * @param steps Steps to move the motor, steps pr revolution (360) is defined above
     * @param dir true = right, false = left
     */
    void move(uint8_t steps, boolean dir);

    void sweep();
};


#endif
