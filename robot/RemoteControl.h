//
// Created by Viktor Hundahl Strate on 20/11/2017.
//

#ifndef LIDARROBOT_REMOTECONTROL_H
#define LIDARROBOT_REMOTECONTROL_H


#include "ArduinoLoopable.h"
#include "Motor.h"

class RemoteControl : ArduinoLoopable {
public:
    void start() override;
    void loop() override;

protected:
    Motor motor;
};


#endif //LIDARROBOT_REMOTECONTROL_H
