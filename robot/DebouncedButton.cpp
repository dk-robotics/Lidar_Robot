#include "DebouncedButton.h"
#include <Arduino.h>

DebouncedButton::DebouncedButton(char pin) {
	this->pin = pin;
	pinMode(pin, INPUT_PULLUP);
	mode = Mode::single;
	time = -1;
}

void DebouncedButton::setMode(Mode mode) {
	this->mode = mode;
}

boolean DebouncedButton::getDebounced() {
	int in = digitalRead(pin);
    if(in != state && (millis() - time > DEBOUNCE_DELAY || time == -1)) {
        state = in;
        time = millis();
    }
    return !state;
}

boolean DebouncedButton::getState() {
	boolean toReturn;
	switch(mode) {
		case Mode::noDebounce:
			toReturn = !digitalRead(pin);
			break;
		case Mode::hold:
			toReturn = getDebounced();
			break;
		case Mode::single:
			boolean oldState = state;
			toReturn = getDebounced() && state != oldState;
			break;
		case Mode::toggle:
			if(getDebounced())
				toggled = !toggled;
			toReturn = toggled;
			break;
	}
	return toReturn;
}
