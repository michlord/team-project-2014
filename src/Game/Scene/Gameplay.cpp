#include <EngineSystem/Entity/EntityManager.h>
#include <EngineSystem/Entity/MessageDispatcher.h>
#include <Game/Entity/Door.h>
#include <Game/Scene/Gameplay.h>
#include <Game/Level/Tile.h>
#include <EngineSystem/Config/Config.h>

#include <Game/AI/ZombieAI.h>

#include <Game/Scene/Intro.h>

namespace Scene {

sf::Vector2f Gameplay::cameraCenter;

Gameplay::Gameplay(SceneStack* sceneStack_, unsigned int levelID_)
 : FrameListener(sceneStack_),
   entityDispatcher(this)
{
    gameplayInitialized = false;
    levelID = levelID_;
}

Gameplay::~Gameplay() {
    Entity::EntityManager::getInstance().unregisterEntity(player.get());
    Entity::EntityManager::getInstance().unregisterEntity(hud.get());

    for(auto& enemy : enemiesEntities)
        Entity::EntityManager::getInstance().unregisterEntity(enemy.get());
    
    for(auto& enemyAI : enemiesAIs)
        Entity::EntityManager::getInstance().unregisterEntity(enemyAI.get());
    
    for(auto& spellSource : spellSourceEntities)
        Entity::EntityManager::getInstance().unregisterEntity(spellSource.get());

    for(auto& specialEntity : specialEntities)
        Entity::EntityManager::getInstance().unregisterEntity(specialEntity.get());

    Log::get().write(Log::System::Game, "Level %d destroyed", level->getID());
}

void Gameplay::initGameplay() {
    Config &cfg = Config::Get();
    cfg.load("assets/config.ini");

    frameContext.assetsManager->loadTexture("assets/images/player_character.png", "player_character");
    frameContext.assetsManager->loadTexture("assets/images/knight_character.png", "knight_character");
    frameContext.assetsManager->loadTexture("assets/images/spells.png", "spells");

    hud = std::unique_ptr<HUD::HUD>(new HUD::HUD());
    Entity::EntityManager::getInstance().registerEntity(hud.get());

    Level::levelManager.initTextures();

    initLevel(levelID);
    initInputHandler();

    gameplayInitialized = true;
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
    //context.addState("jump", std::bind(&Entity::CharacterEntity::handleInput, player.get(), Input::ID::Space, std::placeholders::_1));
    context.addAction("jump", std::bind(&Entity::CharacterEntity::handleInput, player.get(), Input::ID::Space, true));
    context.addAction("slash", std::bind(&Entity::CharacterEntity::handleInput, player.get(), Input::ID::X, true));
    context.addAction("cast", std::bind(&Entity::CharacterEntity::handleInput, player.get(), Input::ID::Z, true));

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

void Gameplay::removeDeadEnemies() {
    auto ai_end = std::remove_if(enemiesAIs.begin(), enemiesAIs.end(), [](std::shared_ptr<AI::BaseAI> ai) {
        bool res = ai->character->healthPoints <= 0;
        if(res) {
            Entity::EntityManager::getInstance().unregisterEntity(ai.get());
            Entity::EntityManager::getInstance().unregisterEntity(ai->character);
        }
        return res;
    });
    enemiesAIs.erase(ai_end, enemiesAIs.end());

    auto enemies_end = std::remove_if(enemiesEntities.begin(), enemiesEntities.end(), [](std::shared_ptr<Entity::CharacterEntity> e) {
        return e->healthPoints <= 0;
    });
    enemiesEntities.erase(enemies_end, enemiesEntities.end());
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
    for(auto e : spellSourceEntities) {
        frameContext.window->draw(*e);
    }
    for(auto e : enemiesEntities) {
        frameContext.window->draw(*e);
    }
    frameContext.window->draw(*player);

    for(auto spell : player->castedSpells)
        frameContext.window->draw(*spell);

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


    frameContext.window->draw(*hud);

    return true;
}

bool Gameplay::fixedUpdate(){
    if(false == gameplayInitialized) {
        initGameplay();
    }

    hud->update();
    for(auto ai : enemiesAIs)
        ai->update();

    player->update();

    cameraCenter = player->getFeetPosition();
    for(auto e : specialEntities)
        e->update();
    for(auto e : enemiesEntities)
        e->update();
    for(auto e : spellSourceEntities)
        e->update();
    for(auto spell : player->castedSpells)
        spell->update();

    for(auto e : enemiesEntities) {
        if(player->getCurrentCollisionRect().intersects(e->getCurrentCollisionRect())) {
            Entity::MessageDispatcher::getInstance().registerMessage(e->getId(), player->getId(), Entity::CharacterEntity::EnemyCollision);
            Entity::MessageDispatcher::getInstance().registerMessage(player->getId(), e->getId(), Entity::CharacterEntity::EnemyCollision);
        }

        //enemies spikes collision
        if (level->getTileOnFeet(e->getFeetPosition()) == Level::Tile::Type::Spikes)
            e->setHealthPoints(0);
    }

    //player spikes collision
    if (level->getTileOnFeet(player->getFeetPosition()) == Level::Tile::Type::Spikes) {
        player->setHealthPoints(0);
    }

    for (auto e : spellSourceEntities) {

        if (player->getCurrentCollisionRect().intersects(e->boundingRect)) {
            Entity::MessageDispatcher::getInstance().registerMessage(e->getId(), player->getId(), Entity::CharacterEntity::SpellSourceCollision);
        }
    }

    if (player->healthPoints == 0)
    {
        Scene::Intro *gameOver = new Scene::Intro(frameContext.sceneStack.get());
        gameOver->setCustomMessage("GAME OVER\n");
        frameContext.sceneStack->popScene();
        frameContext.sceneStack->pushScene(gameOver);
    }


    removeDeadEnemies();

    for(auto spell : player->castedSpells) {
        for(auto e : enemiesEntities) {
            if(e->getCurrentCollisionRect().intersects(spell->getCurrentCollisionRect())) {
                spell->applyEffectOn(e.get());
            }
        }
    }
    player->removeExpiredSpells();

    level->checkEndOfLevelCondition();
    return true;
}

Input::InputHandler *Gameplay::getInputHandler(){
    return inputHandler.get();
}

}
