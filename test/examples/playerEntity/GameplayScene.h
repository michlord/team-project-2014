#ifndef GAMEPLAY_SCENE_H_INCLUDED
#define GAMEPLAY_SCENE_H_INCLUDED

#include <EngineApp/SceneStack.h>
#include <EngineApp/FrameListener.h>
#include <EngineApp/FrameContext.h>
#include <EngineSystem/Input/InputHandler.h>

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

using namespace Core;

class Gameplay : public FrameListener {
    private:
        std::vector< std::unique_ptr<sf::Shape> > ground;
    
        std::unique_ptr<Input::InputHandler> inputHandler;
        void initInputHandler();
        void initGround();
    
    public:
        Gameplay(SceneStack* sceneStack_);
        bool render();
        bool fixedUpdate();
        Input::InputHandler *getInputHandler();
};

#endif // GAMEPLAY_SCENE_H_INCLUDED