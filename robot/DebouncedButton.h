#ifndef DebouncedButton_h
#define DebouncedButton_h

#include <Arduino.h>

#define DEBOUNCE_DELAY 50

/**
 * @class DebouncedButton
 * @brief Contains different leves of debouncing of push-buttons.
 * 
 * This class takes care of software-debouncing
 * simple, regular push-buttons, and provides a
 * very high-level interface for accessing them.
 */

class DebouncedButton {
public:

    explicit DebouncedButton(uint8_t pin);

    /**
     * noDebounce mode simply returns the direct
     * input value from digitalRead().
     *
     * hold mode debounces the button, but if the
     * user holds the button for a longer period,
     * then multiple presses will be registered.
     *
     * single mode indicates that only 1 single
     * press will ever be registered until the
     * button has been released again.
     *
     * toggle mode indicates that the button will
     * be simulated as if it was a toggle-button.
     */
    enum Mode {
        noDebounce, hold, single, toggle
    };

    void setMode(Mode mode);

    /**
     * Get the current state of the button, is it being pressed, the state depends on the mode
     * @return the state of the button for the selected mode
     */
    boolean getState();

private:
    uint8_t pin;
    Mode mode;
    long time;
    bool state;
    bool toggled;

    bool getDebounced();
};
