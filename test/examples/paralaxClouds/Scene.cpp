#include "Scene.h"

#include <EngineSystem/Input/Context.h>
#include <EngineSystem/Input/InputHandler.h>
#include <EngineApp/FrameContext.h>

#include <EngineSystem/Assets/AssetsManager.h>

#include <SFML/Graphics.hpp>

void Scene::initLayers() {
    assets.loadTexture("assets/clouds/cumulus-big1.png", "cumulus-big1");
    assets.loadTexture("assets/clouds/cumulus-big2.png", "cumulus-big2");
    assets.loadTexture("assets/clouds/cumulus-big3.png", "cumulus-big3");
    assets.loadTexture("assets/clouds/cumulus-huge.png", "cumulus-huge");
    assets.loadTexture("assets/clouds/cumulus-small1.png", "cumulus-small1");
    assets.loadTexture("assets/clouds/cumulus-small2.png", "cumulus-small2");
    assets.loadTexture("assets/clouds/cumulus-small3.png", "cumulus-small3");
    
    sf::Sprite sprite(assets.getTexture("cumulus-big1"));
    sprite.setPosition(0.0f, 0.0f);
    layers[0].push_back(sprite);
    sprite.setPosition(-50.0f, 50.0f);
    layers[0].push_back(sprite);
    
    sprite.setPosition(19.0f, 30.0f);
    layers[1].push_back(sprite);
    
    layersScales = {1.0f, 1.5f, 3.0f};
}

void Scene::initInputHandler() {
    Input::Context context(true);
    context.addBinding("right", Input::ID::Right);
    context.addBinding("left", Input::ID::Left);
    context.addBinding("up", Input::ID::Up);
    context.addBinding("down", Input::ID::Down);
    context.addState("right", std::bind(&Scene::moveCamera, this, sf::Vector2f(5.0f, 0.0f)));
    context.addState("left", std::bind(&Scene::moveCamera, this, sf::Vector2f(-5.0f, 0.0f)));
    context.addState("up", std::bind(&Scene::moveCamera, this, sf::Vector2f(0.0f, -5.0f)));
    context.addState("down", std::bind(&Scene::moveCamera, this, sf::Vector2f(0.0f, 5.0f)));
    
    Input::InputHandler::ContextVector contextVector;
    contextVector.push_back(context);
    inputHandler.reset(new Input::InputHandler(contextVector));
}

void Scene::moveCamera(sf::Vector2f direction) {
    cameraCenter += direction;
}

Scene::Scene(SceneStack* sceneStack_)
 : FrameListener(sceneStack_)
{
    cameraCenter = sf::Vector2f(0.0f, 0.0f);
    initInputHandler();
    initLayers();
}

bool Scene::render() {
    for(unsigned int i = 0; i < layers.size(); ++i) {
        sf::View view;
        view.setCenter(cameraCenter * layersScales[i]);
        frameContext.window->setView(view);
        
        auto it = layers[i].begin();
        auto end = layers[i].end();
        while(it != end) {
            frameContext.window->draw(*it);
            ++it;
        }
    }
    return true;
}

bool Scene::fixedUpdate() {
    return true;
}

Input::InputHandler *Scene::getInputHandler() {
    return inputHandler.get();
}
