#include "StateManager.h"
#include "FormelSIT.h"

StateManager::StateManager() {
    currentState = new FormelSIT();
}

void StateManager::start() {
    currentState->start();
}

void StateManager::loop() {
    currentState->loop();
}

StateManager::~StateManager() {
    delete currentState;
}
