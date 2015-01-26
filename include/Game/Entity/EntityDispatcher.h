#ifndef GAME_ENTITY_ENTITY_DISPATCHER_H_INCLUDED
#define GAME_ENTITY_ENTITY_DISPATCHER_H_INCLUDED

#include <EngineSystem/Entity/BaseEntity.h>
#include <Game/Entity/CharacterEntity/CharacterEntity.h>

namespace Scene {
    class Gameplay;
}

namespace Entity {

    class EntityDispatcher {
        public:
            EntityDispatcher(Scene::Gameplay *gameplay_);
            void createEntity(const float x, const float y, const std::string& id);

        protected:
            void createPlayer(const float x, const float y);
            void createEnemyEntity(const float x, const float y, const std::string& id);
            void createSpecialEntity(const float x, const float y, const std::string& id);
            void createSpellSourceEntity(const float x, const float y, const std::string& id);

            Scene::Gameplay *gameplay;
    };
}

#endif /* GAME_ENTITY_ENTITY_DISPATCHER_H_INCLUDED */