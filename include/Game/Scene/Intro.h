#ifndef GAME_SCENE_INTRO_INCLUDED_H
#define GAME_SCENE_INTRO_INCLUDED_H

#include <EngineApp/SceneStack.h>
#include <EngineApp/FrameListener.h>
#include <EngineApp/FrameContext.h>

using namespace Core;

namespace Scene {

class Intro : public FrameListener {
    private:
    
    public:
        Intro(SceneStack* sceneStack_);
        void render();
        void fixedUpdate();
        bool isExclusive();
};

}

#endif // GAME_SCENE_INTRO_INCLUDED_H