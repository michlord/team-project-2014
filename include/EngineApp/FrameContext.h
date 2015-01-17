#ifndef ENGINE_APP_FRAME_CONTEXT_H_INCLUDED
#define ENGINE_APP_FRAME_CONTEXT_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <memory>
#include "SceneStack.h"
#include "WindowContext.h"

namespace Core {

class FrameContext {
    private:
        FrameContext();
    public:
        static FrameContext &getInstance();
        sf::RenderWindow* window;
        WindowContext *appWindow;
        float frameTime;
        float deltaTime;
        std::unique_ptr<SceneStack> sceneStack;
};

extern FrameContext &frameContext;

}

#endif // ENGINE_APP_FRAME_CONTEXT_H_INCLUDED