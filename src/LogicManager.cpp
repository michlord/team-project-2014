#include "LogicManager.h"

LogicManager::LogicManager() {

}

LogicManager::~LogicManager() {

}

void LogicManager::handleLogic() {
    computeFrameTime();

    // switch(GAMESTATE) {
    //    case GAMEPLAY: handleGameplayLogic(); break;
    //    case MENU: handleMenuLogic(); break;
    //    ...
    // }
}

void LogicManager::computeFrameTime() {
    frameTime = frameTimeClock.restart();
}

sf::Time LogicManager::getFrameTime() {
    return sf::Time(frameTime);
}