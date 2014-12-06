#include "GameplayScene.h"
#include <EngineSystem/Input/Context.h>
#include <EngineSystem/Input/InputHandler.h>
#include <EngineApp/FrameContext.h>

#include <memory>
#include <vector>

void Gameplay::initInputHandler() {
    Input::Context context(true);
    context.addBinding("right", Input::ID::Right);
    context.addBinding("left", Input::ID::Left);
    context.addBinding("jump", Input::ID::D);
    context.addBinding("crouch", Input::ID::Down);
    context.addBinding("slash", Input::ID::F);
    context.addBinding("cast", Input::ID::S);
    
    context.addBinding("right", Input::ID::GamepadDPadRight);
    context.addBinding("left", Input::ID::GamepadDPadLeft);
    context.addBinding("jump", Input::ID::GamepadButtonA);
    context.addBinding("crouch", Input::ID::GamepadDPadDown);
    context.addBinding("slash", Input::ID::GamepadButtonX);
    context.addBinding("cast", Input::ID::GamepadButtonY);
    
    Input::InputHandler::ContextVector contextVector;
    contextVector.push_back(context);
    
    inputHandler.reset(new Input::InputHandler(contextVector));
}

void Gameplay::initGround() {
    sf::Shape *tmp = nullptr;
    tmp = new sf::RectangleShape(sf::Vector2f(100.0f, 50.0f));
    tmp->setPosition(10.0f, 300.0f);
    tmp->setFillColor(sf::Color::Green);
    ground.push_back(std::unique_ptr<sf::Shape>(tmp));
    
    tmp = new sf::RectangleShape(sf::Vector2f(600.0f, 50.0f));
    tmp->setPosition(110.0f, 350.0f);
    tmp->setFillColor(sf::Color::Green);
    ground.push_back(std::unique_ptr<sf::Shape>(tmp));
    
    tmp = new sf::RectangleShape(sf::Vector2f(100.0f, 50.0f));
    tmp->setPosition(400.0f, 200.0f);
    tmp->setFillColor(sf::Color::Green);
    ground.push_back(std::unique_ptr<sf::Shape>(tmp));
    
    
}

Gameplay::Gameplay(SceneStack* sceneStack_)
 : FrameListener(sceneStack_)
{
    initInputHandler();
    initGround();
}

bool Gameplay::render() {
    auto it = ground.begin();
    auto end = ground.end();
    while(it != end) {
        sf::Shape& part = **it;
        
        Core::frameContext.window->draw(part);
        
        ++it;
    }
    
    
    
    return true;
}

bool Gameplay::fixedUpdate() {
    return true;
}

Input::InputHandler *Gameplay::getInputHandler() {
    return inputHandler.get();
}