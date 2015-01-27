#ifndef GAME_SCENE_GAMEPLAY_H_INCLUDED
#define GAME_SCENE_GAMEPLAY_H_INCLUDED

#include <EngineApp/SceneStack.h>
#include <EngineApp/FrameListener.h>
#include <EngineApp/FrameContext.h>

#include <EngineSystem/Input/InputHandler.h>
#include <EngineSystem/Assets/AssetsManager.h>

#include <Game/HUD/HUD.h>
#include <Game/Level/LevelManager.h>
#include <Game/Level/Level.h>

#include <Game/Entity/CharacterEntity/CharacterEntity.h>
#include <Game/Entity/EntityDispatcher.h>
#include <Game/Entity/Spells/SpellSource.h>

#include <Game/AI/BaseAI.h>

#include <memory>
#include <vector>

using namespace Core;

namespace Scene {

    class Gameplay : public FrameListener {
        private:
            std::unique_ptr<Input::InputHandler> inputHandler;
            void initInputHandler();
            void initLevel(unsigned int id);
            void moveCamera(const sf::Vector2f& direction);
            void removeDeadEnemies();

            HUD::HUD hud;
            Level::Level *level;
            Entity::EntityDispatcher entityDispatcher;
            std::shared_ptr<Entity::CharacterEntity> player;
            std::vector<std::shared_ptr<Entity::CharacterEntity>> enemiesEntities;
            std::vector<std::shared_ptr<AI::BaseAI>> enemiesAIs;
            std::vector<std::shared_ptr<Entity::Spells::SpellSource>> spellSourceEntities;
            std::vector<std::shared_ptr<Entity::BaseEntity>> specialEntities;

        public:
            Gameplay(SceneStack* sceneStack_, unsigned int levelID);
            bool render();
            bool fixedUpdate();
            Input::InputHandler *getInputHandler();

            static sf::Vector2f cameraCenter;

            friend class Entity::EntityDispatcher;
    };

}

#endif // GAME_SCENE_GAMEPLAY_H_INCLUDED
