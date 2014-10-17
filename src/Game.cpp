#include "Game.h"
#include <SFML/Graphics.hpp>

Game::Game() {
    isEnd = false;

    window = new Rendering::Window();
    librariesManager = new LibrariesManager();
    inputManager = new InputManager();
    logicManager = new LogicManager();
    physicsManager = new PhysicsManager();
    renderingManager = new RenderingManager();
}

Game::~Game() {
    delete renderingManager;
    delete physicsManager;
    delete logicManager;
    delete inputManager;
    delete librariesManager;
    delete window;
}

Game& Game::get() {
    static Game instance;
    return instance;
}

void Game::init() {
    getLibrariesManager().loadLibraries();
    getWindow().open(800, 600, "Window title");
}

void Game::start() {
    isEnd = false;

    while(isEnd == false) {
        getInputManager().handleInput();
        getLogicManager().handleLogic();
        getPhysicsManager().updatePhysics();
        getRenderingManager().render();
    }
}

void Game::pause() {

}

void Game::resume() {

}

void Game::end() {
    getWindow().close();
    getLibrariesManager().releaseLibraries();
}

/**
 * Setters and getters
 **/

Rendering::Window& Game::getWindow() {
    return *window;
}

LibrariesManager& Game::getLibrariesManager() {
    return *librariesManager;
}

InputManager& Game::getInputManager() {
    return *inputManager;
}

LogicManager& Game::getLogicManager() {
    return *logicManager;
}

PhysicsManager& Game::getPhysicsManager() {
    return *physicsManager;
}

RenderingManager& Game::getRenderingManager() {
    return *renderingManager;
}
