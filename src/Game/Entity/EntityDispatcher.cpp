#include <Game/Scene/Gameplay.h>
#include "Game/Entity/EntityDispatcher.h"

namespace Scene {
namespace Helpers {
    std::map<std::string, sf::FloatRect> makePlayerAnimation(Video::Render::Animation &animation);
}
}

namespace Entity {

EntityDispatcher::EntityDispatcher(Scene::Gameplay *gameplay_) {
    gameplay = gameplay_;
}

void EntityDispatcher::createEntity(const float x, const float y, std::string id) {
    if(id == "player")
        createPlayer(x, y);
}

void EntityDispatcher::createPlayer(const float x, const float y) {
    Video::Render::Animation animation;
    std::map<std::string, sf::FloatRect> collisionRects = Scene::Helpers::makePlayerAnimation(animation);

    gameplay->player.reset(new Entity::CharacterEntity(Entity::EntityType::Player, animation, sf::FloatRect(x, y, 50.0f, 64.0f), gameplay->level));
    gameplay->player->collisionRects = collisionRects;
    gameplay->player->flipped = false;
}

void EntityDispatcher::createEnemyEntity(const float x, const float y) {
    float s = x + y;
    s++;
}

void EntityDispatcher::createSpecialEnityty(const float x, const float y) {
    float s = x + y;
    s++;
}

}