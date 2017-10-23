//
// Created by Viktor Hundahl Strate on 23/10/2017.
// This class manages the state of the robot, states includes FormelSIT or Minesweeper
//

#ifndef LIDARROBOT_STATEMANAGER_H
#define LIDARROBOT_STATEMANAGER_H


#include "ArduinoLoopable.h"

class StateManager : public ArduinoLoopable {
public:
    StateManager();

    virtual ~StateManager();

    void start() override;
    void loop() override;

protected:
    ArduinoLoopable* currentState;
};


#endif //LIDARROBOT_STATEMANAGER_H
