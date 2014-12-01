#ifndef ENGINE_APP_FRAME_LISTENER_H_INCLUDED
#define ENGINE_APP_FRAME_LISTENER_H_INCLUDED

#include "SceneStack.h"
#include <EngineSystem/Input/InputHandler.h>

namespace Core {

class SceneStack;

class FrameListener {
    private:
        SceneStack* sceneStack;
    protected:
        void pushScene(FrameListener* scene);
        void popScene();
        void clearScenes();
    public:
        FrameListener(SceneStack* sceneStack_);
        virtual ~FrameListener();
        virtual bool render()      = 0;
        virtual bool fixedUpdate() = 0;
        virtual Input::InputHandler *getInputHandler();
};

}

#endif // ENGINE_APP_FRAME_LISTENER_H_INCLUDED