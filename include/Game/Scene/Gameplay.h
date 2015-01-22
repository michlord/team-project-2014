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

            HUD::HUD hud;
            Level::Level *level;
        public:
            Gameplay(SceneStack* sceneStack_, unsigned int levelID);
            bool render();
            bool fixedUpdate();
            Input::InputHandler *getInputHandler();
            
            static sf::Vector2f cameraCenter;
    };

}

#endif // GAME_SCENE_GAMEPLAY_H_INCLUDED
