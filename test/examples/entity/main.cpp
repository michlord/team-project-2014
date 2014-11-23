#define _VARIADIC_MAX 8 // Visual studio std::bind has a bug...

#include <iostream>
#include <functional>
#include <memory>

#include <SFML/Graphics.hpp>

#include <EngineSystem/Input/Context.h>
#include <EngineSystem/Input/InputHandler.h>

#include "Animation.h"

#include <EngineSystem/Entity/EntityManager.h>
#include <EngineSystem/Entity/MessageDispatcher.h>
#include "PlayerEntity.h"
#include "PlayerStates.h"

sf::Texture texture;
sf::Time frameTime;

Animation prepareAnimation() {
    Animation anim;
    Video::Render::AnimatedSprite jumpSprite;
    Video::Render::AnimatedSprite idleSprite;
    
    Video::Render::Sprite::Frame jump[4];
    Video::Render::Sprite::Frame idle[2];
    //Video::Render::Sprite::Frame slash[6];
    
    jump[0].setTextureSegment(sf::IntRect(8, 60, 56, 56));
    jump[1].setTextureSegment(sf::IntRect(65, 60, 56, 56));
    jump[2].setTextureSegment(sf::IntRect(122, 60, 56, 56));
    jump[3].setTextureSegment(sf::IntRect(179, 60, 56, 56));
    
    idle[0].setTextureSegment(sf::IntRect(3, 3, 56, 56));
    idle[1].setTextureSegment(sf::IntRect(60, 3, 56, 56));
    
    for(auto frame : jump) {
        frame.setDuration(sf::seconds(0.15f));
        jumpSprite.insertFrame(frame);
    }
    
    for(auto frame : idle) {
        frame.setDuration(sf::seconds(0.15f));
        idleSprite.insertFrame(frame);
    }
    
    idleSprite.bindTexture(texture);
    jumpSprite.bindTexture(texture);

    anim.addAnimation("idle", idleSprite);
    anim.addAnimation("jump", jumpSprite);
    
    anim.setAnimation("idle");
    return anim;
}



int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Example");
    window.setKeyRepeatEnabled(false);
    sf::Clock clock;
    
    
    if(texture.loadFromFile("assets/elisa-spritesheet1.png") == false) {
        std::cerr << "Error loading texture file" << std::endl;
        return 1;
    }
    
    Animation anim = prepareAnimation();
    anim.setPosition(50,50);
    anim.setSize(112,112);

    PlayerEntity playerEntity(5);
    playerEntity.animation = anim;
    
    Entity::EntityManager::getInstance().registerEntity(&playerEntity);


    
    std::function<void()> jumpCallback = std::bind(
        &Entity::MessageDispatcher::registerMessage,
        &(Entity::MessageDispatcher::getInstance()),
        0,
        5,
        (int) PLAYER_MESSAGES::Jump,
        0.0f,
        nullptr
    );
    
    Input::Context context(true);
    context.addBinding("jump", Input::ID::Space);
    context.addBinding("jump", Input::ID::GamepadButtonA);
    context.addAction("jump", jumpCallback);
    Input::InputHandler::ContextVector contextVector;
    contextVector.push_back(context);
    Input::InputHandler inputHandler(contextVector);
    
    sf::Event event;
    clock.restart();
    while (window.isOpen()) {
        frameTime = clock.restart();
        while (window.pollEvent(event)) {
            // Window closed or escape key pressed: exit
            if ((event.type == sf::Event::Closed) || 
               ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))) {
                window.close();
                break;
            }
            std::unique_ptr<Input::Input> input_p(Input::translateEvent(event));
            if(input_p) {
                inputHandler.handleInput(*input_p);
            }
        }
        
        playerEntity.update();
        window.clear(sf::Color(50, 200, 50));
        playerEntity.animation.draw(&window);
        window.display();
    }
    return EXIT_SUCCESS;
}