#ifndef GAME_SCENE_GAMEPLAY_H_INCLUDED
#define GAME_SCENE_GAMEPLAY_H_INCLUDED

#include <EngineApp/SceneStack.h>
#include <EngineApp/FrameListener.h>
#include <EngineApp/FrameContext.h>

#include <EngineSystem/Input/InputHandler.h>
#include <EngineSystem/Assets/AssetsManager.h>

#include <memory>
#include <vector>

using namespace Core;

namespace Scene {

    class Gameplay : public FrameListener {
        private:
            std::unique_ptr<Input::InputHandler> inputHandler;
            void initInputHandler();
            void initLevel(unsigned int id);

            sf::Vector2f cameraCenter;
        public:
            Gameplay(SceneStack* sceneStack_, unsigned int levelID);
            bool render();
            bool fixedUpdate();
            Input::InputHandler *getInputHandler();
    };

}

#endif // GAME_SCENE_GAMEPLAY_H_INCLUDED
