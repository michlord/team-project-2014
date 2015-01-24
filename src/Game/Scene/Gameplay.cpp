#include <Game/Scene/Gameplay.h>
#include <Game/Level/Tile.h>
#include <EngineSystem/Config/Config.h>

namespace Scene {

namespace Helpers {
    std::map<std::string, sf::FloatRect> makePlayerAnimation(Video::Render::Animation &animation);
}

sf::Vector2f Gameplay::cameraCenter;

Gameplay::Gameplay(SceneStack* sceneStack_, unsigned int levelID)
 : FrameListener(sceneStack_),
   entityDispatcher(this)
{
    (void) levelID;

    Config &cfg = Config::Get();
    cfg.load("assets/config.ini");

    Level::levelManager.initTextures();

    Video::Render::Animation animation;
    std::map<std::string, sf::FloatRect> collisionRects = Helpers::makePlayerAnimation(animation);

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


    context.addState("left", std::bind(&Entity::CharacterEntity::handleInput, player.get(), Input::ID::Left, std::placeholders::_1));
    context.addState("right", std::bind(&Entity::CharacterEntity::handleInput, player.get(), Input::ID::Right, std::placeholders::_1));
    context.addState("jump", std::bind(&Entity::CharacterEntity::handleInput, player.get(), Input::ID::Space, std::placeholders::_1));
    //context.addAction("jump", std::bind(&Entity::CharacterEntity::handleInput, player.get(), Input::ID::Space, true));
    // context.addState("right", std::bind(&Gameplay::moveCamera, this, sf::Vector2f(5.0f, 0.0f)));
    // context.addState("up", std::bind(&Gameplay::moveCamera, this, sf::Vector2f(0.0f, -5.0f)));
    // context.addState("crouch", std::bind(&Gameplay::moveCamera, this, sf::Vector2f(0.0f, 5.0f)));

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
    level = &Level::levelManager.getCurrentLevel();
    Level::levelManager.loadLevel(id, &entityDispatcher);
}

void Gameplay::moveCamera(const sf::Vector2f& direction) {
    cameraCenter += direction;
}

bool Gameplay::render(){

    sf::View view;
    view.setCenter(cameraCenter);
    view.zoom(0.5f);
    frameContext.window->setView(view);

    frameContext.window->draw(*level);

    for(auto e : specialEntities) {
        frameContext.window->draw(*e);
    }
    for(auto e : enemiesEntities) {
        frameContext.window->draw(*e);
    }
    frameContext.window->draw(*player);

    // Collision additonal data
    std::vector<std::shared_ptr<Entity::CharacterEntity>> characters = enemiesEntities;
    characters.push_back(player);
    for(auto e : characters) {
        sf::RectangleShape rectangle;
        sf::FloatRect r = e->getCurrentCollisionRect();

        rectangle.setPosition(r.left, r.top);
        rectangle.setSize(sf::Vector2f(r.width, r.height));
        rectangle.setOutlineColor(sf::Color::Red);
        rectangle.setFillColor(sf::Color(100,100,100,180));
        frameContext.window->draw(rectangle);

        sf::CircleShape feet(5);
        feet.setPosition(e->getFeetPosition() - sf::Vector2f(5.0f, 5.0f));
        feet.setFillColor(sf::Color(100,150,100,180));
        frameContext.window->draw(feet);
    }

    frameContext.window->setView(frameContext.window->getDefaultView());


    frameContext.window->draw(hud);

    return true;
}

bool Gameplay::fixedUpdate(){
    hud.update();
    player->update();
    cameraCenter = player->getFeetPosition();
    for(auto e : specialEntities)
        e->update();
    for(auto e : enemiesEntities)
        e->update();

    return true;
}

Input::InputHandler *Gameplay::getInputHandler(){
    return inputHandler.get();
}

}
