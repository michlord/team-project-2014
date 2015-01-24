#include "Game/Entity/EntityDispatcher.h"
#include <Game/Scene/Gameplay.h>
#include <Game/Entity/Door.h>
#include <EngineSystem/Entity/EntityManager.h>

namespace Scene {
namespace Helpers {
    std::map<std::string, sf::FloatRect> makePlayerAnimation(Video::Render::Animation &animation);
    std::map<std::string, sf::FloatRect> makeKnightAnimation(Video::Render::Animation &animation);
}
}

namespace Entity {

EntityDispatcher::EntityDispatcher(Scene::Gameplay *gameplay_) {
    gameplay = gameplay_;
}

void EntityDispatcher::createEntity(const float x, const float y, const std::string& id) {
    if(id == "player") {
        createPlayer(x, y);
    } else if(id == "knight") {
        createEnemyEntity(x, y, id);
    } else if(id == "door") {
        createSpecialEntity(x, y, id);
    } else {
        Log::get().write(Log::System::Game, "Attempt to create unknown entity: '%s'", id.c_str());
    }
}

void EntityDispatcher::createPlayer(const float x, const float y) {
    Video::Render::Animation animation;
    std::map<std::string, sf::FloatRect> collisionRects = Scene::Helpers::makePlayerAnimation(animation);

    gameplay->player.reset(new Entity::CharacterEntity((int)Entity::EntityType::Player, animation, sf::FloatRect(x, y, 50.0f, 64.0f), gameplay->level));
    gameplay->player->collisionRects = collisionRects;
    gameplay->player->flipped = false;
}

void EntityDispatcher::createEnemyEntity(const float x, const float y, const std::string& id) {
    if(id == "knight") {
        Video::Render::Animation animation;
        std::map<std::string, sf::FloatRect> collisionRects = Scene::Helpers::makeKnightAnimation(animation);

        Entity::CharacterEntity* enemy = new Entity::CharacterEntity(
            -1, 
            animation, 
            sf::FloatRect(x, y, 40.0f, 82.0f), 
            gameplay->level
        ); 
        enemy->collisionRects = collisionRects;
        enemy->flipped = false;
        Entity::EntityManager::getInstance().registerEntity(enemy);
        gameplay->enemiesEntities.push_back(std::shared_ptr<Entity::CharacterEntity>(enemy));
    }
}

void EntityDispatcher::createSpecialEntity(const float x, const float y, const std::string& id) {
    if(id == "door") {
        Entity::Door* door = new Entity::Door((int)Entity::EntityType::Door, sf::Vector2f(x, y));
        gameplay->specialEntities.push_back(std::shared_ptr<Entity::BaseEntity>(door));
    }
}

}