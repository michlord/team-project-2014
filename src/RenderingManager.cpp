#include "RenderingManager.h"
#include "Game.h"

RenderingManager::RenderingManager() {

}

RenderingManager::~RenderingManager() {

}

void RenderingManager::render() {
    Game::get().getWindow().clear();

    {
        // Rendering here
    }

    Game::get().getWindow().display();
}