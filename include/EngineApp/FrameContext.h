#ifndef ENGINE_APP_FRAME_CONTEXT_H_INCLUDED
#define ENGINE_APP_FRAME_CONTEXT_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <memory>
#include "SceneStack.h"

namespace Core {

struct FrameContext {
    sf::RenderWindow* window;
    float frameTime;
    float deltaTime;
    std::unique_ptr<SceneStack> sceneStack;
};

extern FrameContext frameContext;

}

#endif // ENGINE_APP_FRAME_CONTEXT_H_INCLUDED