#include <Game/Scene/Gameplay.h>
#include <Game/Level/Tile.h>
#include <EngineSystem/Config/Config.h>

namespace Scene {

sf::Vector2f Gameplay::cameraCenter;

Gameplay::Gameplay(SceneStack* sceneStack_, unsigned int levelID)
 : FrameListener(sceneStack_)
{
    (void) levelID;

    Config &cfg = Config::Get();
    cfg.load("assets/config.ini");
    
    Level::levelManager.initTextures();

    initLevel(levelID);
    initInputHandler();

}

void Gameplay::initInputHandler() {
    Config &cfg = Config::Get();

    Input::Context context(true);
    context.addBinding("right",  (Input::ID) cfg.getInt("keys", "right", Input::ID::Right));
    context.addBinding("left",   (Input::ID) cfg.getInt("keys", "left",  Input::ID::Left));
    context.addBinding("crouch", (Input::ID) cfg.getInt("keys", "down",  Input::ID::Down));
    context.addBinding("jump",   (Input::ID) cfg.getInt("keys", "jump",  Input::ID::D));
    context.addBinding("slash",  (Input::ID) cfg.getInt("keys", "slash", Input::ID::F));
    context.addBinding("cast",   (Input::ID) cfg.getInt("keys", "magic", Input::ID::S));

    // Temporary keyboard camera moving
    context.addBinding("up", Input::ID::Up);
    context.addState("left", std::bind(&Gameplay::moveCamera, this, sf::Vector2f(-5.0f, 0.0f)));
    context.addState("right", std::bind(&Gameplay::moveCamera, this, sf::Vector2f(5.0f, 0.0f)));
    context.addState("up", std::bind(&Gameplay::moveCamera, this, sf::Vector2f(0.0f, -5.0f)));
    context.addState("crouch", std::bind(&Gameplay::moveCamera, this, sf::Vector2f(0.0f, 5.0f)));

    // context.addState("right", std::bind(&PlayerEntity::right, player.get(), std::placeholders::_1));
    // context.addState("left", std::bind(&PlayerEntity::left, player.get(), std::placeholders::_1));
    // context.addState("down", std::bind(&PlayerEntity::down, player.get(), std::placeholders::_1));
    // context.addAction("jump", std::bind(&PlayerEntity::jump, player.get()));
    // context.addAction("slash", std::bind(&PlayerEntity::slash, player.get()));
    // context.addAction("cast", std::bind(&PlayerEntity::cast, player.get()));

    Input::InputHandler::ContextVector contextVector;
    contextVector.push_back(context);

    inputHandler.reset(new Input::InputHandler(contextVector));
}

void Gameplay::initLevel(unsigned int id) {
    Level::levelManager.loadLevel(id);
    level = &Level::levelManager.getCurrentLevel();
}

void Gameplay::moveCamera(const sf::Vector2f& direction) {
    cameraCenter += direction;
}

bool Gameplay::render(){
    frameContext.window->draw(*level);
    frameContext.window->draw(hud);

    return true;
}

bool Gameplay::fixedUpdate(){
    hud.update();

    return true;
}

Input::InputHandler *Gameplay::getInputHandler(){
    return inputHandler.get();
}

}
