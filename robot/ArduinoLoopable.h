//
// Created by Viktor Hundahl Strate on 23/10/2017.
// An abstract class for classes that has a start and a loop function
//

#ifndef LIDARROBOT_ARDUINOLOOPABLE_H
#define LIDARROBOT_ARDUINOLOOPABLE_H


class ArduinoLoopable {
public:
    // Start function is called when the Arduino starts
    virtual void start() {};

    // Loop function is called when every time the last loop ended
    virtual void loop() {};
};


#endif //LIDARROBOT_ARDUINOLOOPABLE_H
