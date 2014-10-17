#include "LogicManager.h"

LogicManager::LogicManager() {

}

LogicManager::~LogicManager() {

}

void LogicManager::handleLogic() {
    computeFrameTime();

    // Handle logic here
}

void LogicManager::computeFrameTime() {
    frameTime = frameTimeClock.restart();
}