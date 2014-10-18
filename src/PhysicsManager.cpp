#include "PhysicsManager.h"
#include "Game.h"

PhysicsManager::PhysicsManager() {

}

PhysicsManager::~PhysicsManager() {

}

/**
 * Real-time loop.
 * This method implements 'real time loop' (semi-fixed timestep) based on time of frame. 
 * Do not change anything unless you know what you are doing.
 */
void PhysicsManager::updatePhysics() {
    sf::Int64 microsecFrameTime = Game::get().getLogicManager().getFrameTime().asMicroseconds();
    sf::Int64 microsecMaxDeltaTime = 10 * 1000; // 10ms
    sf::Int64 microsecCurrentInterval;

    while(microsecFrameTime > 0) {
        microsecCurrentInterval = std::min(microsecFrameTime, microsecMaxDeltaTime);
        updatePhysics(microsecCurrentInterval);
        microsecFrameTime -= microsecCurrentInterval;
    }
}

void PhysicsManager::updatePhysics(sf::Int64 microsecDeltaTime) {
    // Update game objects here
}