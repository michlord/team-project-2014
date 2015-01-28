#ifndef GAME_SCENE_INTRO_INCLUDED_H
#define GAME_SCENE_INTRO_INCLUDED_H

#include <EngineApp/SceneStack.h>
#include <EngineApp/FrameListener.h>
#include <EngineApp/FrameContext.h>

#include <EngineSystem/Assets/AssetsManager.h>
#include <SFML/Graphics/Text.hpp>

#include <EngineSystem/Input/InputHandler.h>



using namespace Core;

namespace Scene {

class Intro : public FrameListener {
    private:
        Assets::AssetsManager assets;
        sf::Text              headlineText;
        
        std::unique_ptr<Input::InputHandler> inputHandler;
    public:
        Intro(SceneStack* sceneStack_);
        bool render();
        bool fixedUpdate();
        void setCustomMessage(std::string customMessage);
        Input::InputHandler *getInputHandler();
};

}

#include <Game/Scene/MainMenu.h>

#endif // GAME_SCENE_INTRO_INCLUDED_H