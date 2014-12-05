#ifndef GAMEPLAY_SCENE_H_INCLUDED
#define GAMEPLAY_SCENE_H_INCLUDED

#include <EngineApp/SceneStack.h>
#include <EngineApp/FrameListener.h>
#include <EngineApp/FrameContext.h>

using namespace Core;

class Gameplay : public FrameListener {
    private:
    
    public:
        Gameplay(SceneStack* sceneStack_);
        bool render();
        bool fixedUpdate();
};

#endif // GAMEPLAY_SCENE_H_INCLUDED