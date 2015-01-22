#include <Game/Scene/Gameplay.h>
#include <EngineSystem/Config/Config.h>

namespace Scene {

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

bool Gameplay::render(){
    frameContext.window->draw(*level);

    return true;
}

bool Gameplay::fixedUpdate(){
    return true;
}

Input::InputHandler *Gameplay::getInputHandler(){
    return inputHandler.get();
}


}
