#include <Game/Entity/AnimationLoader.h>
#include <Game/Entity/EntityDispatcher.h>
#include <Game/Scene/Gameplay.h>
#include <Game/Entity/Door.h>
#include <Game/Entity/Spells/SpellSource.h>
#include <Game/AI/BaseAI.h>
#include <Game/AI/ZombieAI.h>
#include <EngineSystem/Entity/EntityManager.h>

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
        } else if(id == "fireSource" || id == "natureSource" || id == "windSource" || id == "iceSource") {
            createSpellSourceEntity(x, y, id);
        } else {
            Log::get().write(Log::System::Game, "Attempt to create unknown entity: '%s'", id.c_str());
        }
    }

    void EntityDispatcher::createPlayer(const float x, const float y) {
        Video::Render::Animation animation;
        std::map<std::string, sf::FloatRect> collisionRects;

        animation = Entity::AnimationLoader::loadAnimation(
            "assets/animations/player.anim",
            frameContext.assetsManager->getTexture("player_character")
        );
        collisionRects = Entity::AnimationLoader::loadCollision("assets/animations/player.coll");

        gameplay->player.reset(new Entity::CharacterEntity((int)Entity::EntityType::Player, animation, sf::FloatRect(x, y, 50.0f, 64.0f), gameplay->level));
        gameplay->player->collisionRects = collisionRects;
        gameplay->player->flipped = false;

        Entity::EntityManager::getInstance().registerEntity(gameplay->player.get());
    }

    void EntityDispatcher::createEnemyEntity(const float x, const float y, const std::string& id) {
        if(id == "knight") {
            Video::Render::Animation animation;
            std::map<std::string, sf::FloatRect> collisionRects;

            animation = Entity::AnimationLoader::loadAnimation(
                "assets/animations/knight.anim",
                frameContext.assetsManager->getTexture("knight_character")
            );

            collisionRects = Entity::AnimationLoader::loadCollision("assets/animations/knight.coll");

            Entity::CharacterEntity* enemy = new Entity::CharacterEntity(
                -1,
                animation,
                sf::FloatRect(x, y, 40.0f, 82.0f),
                gameplay->level
            );
            enemy->runSpeed = 2.0f;
            AI::ZombieAI* ai = new AI::ZombieAI(-1, enemy);
            enemy->collisionRects = collisionRects;
            enemy->flipped = false;
            Entity::EntityManager::getInstance().registerEntity(enemy);
            gameplay->enemiesEntities.push_back(std::shared_ptr<Entity::CharacterEntity>(enemy));
            gameplay->enemiesAIs.push_back(std::shared_ptr<AI::BaseAI>(ai));
        }
    }

    void EntityDispatcher::createSpecialEntity(const float x, const float y, const std::string& id) {
        if(id == "door") {
            Entity::Door* door = new Entity::Door((int)Entity::EntityType::Door, sf::Vector2f(x, y));
            Entity::EntityManager::getInstance().registerEntity(door);
            gameplay->specialEntities.push_back(std::shared_ptr<Entity::BaseEntity>(door));
        }
    }

    void EntityDispatcher::createSpellSourceEntity(const float x, const float y, const std::string& id) {
        Entity::Spells::SpellType type = Entity::Spells::None;
        if(id == "fireSource")
            type = Entity::Spells::Fire;
        else if(id == "natureSource")
            type = Entity::Spells::Nature;
        else if(id == "windSource")
            type = Entity::Spells::Wind;
        else if(id == "iceSource")
            type = Entity::Spells::Ice;

        Entity::Spells::SpellSource* spellSource = new Entity::Spells::SpellSource(-1, sf::Vector2f(x, y), type);
        Entity::EntityManager::getInstance().registerEntity(spellSource);
        gameplay->spellSourceEntities.push_back(std::shared_ptr<Entity::Spells::SpellSource>(spellSource));
    }

}
