#include "InputManager.h"
#include "Game.h"

InputManager::InputManager() {

}

InputManager::~InputManager() {

}

void InputManager::handleInput() {
    sf::Event event;

    while(Game::get().getWindow().getHandle().pollEvent(event)) {
        if(event.type == sf::Event::Closed)
            Game::get().isEnd = true;

        else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            Game::get().isEnd = true;
    }
}