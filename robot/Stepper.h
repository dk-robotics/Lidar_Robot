#ifndef Stepper_h
#define Stepper_h

#include <Arduino.h>
#include "PinSetup.h"

#define STEPS_PER_REV 200
#define WAIT_TIME 2

class Stepper {
public:
	Stepper();
	void calibrate();
	void move(uint8_t steps, boolean dir);
	void sweep();
};




#endif
