#include <EngineApp/SceneStack.h>
#include <EngineApp/FrameListener.h>

namespace Core {

void FrameListener::pushScene(FrameListener* scene) {
    sceneStack->pushScene(scene);
}

void FrameListener::popScene() {
    sceneStack->popScene();
}

void FrameListener::clearScenes() {
    sceneStack->clearScenes();
}

FrameListener::FrameListener(SceneStack* sceneStack_)
 : sceneStack(sceneStack_)
{
}

FrameListener::~FrameListener() {

}

bool FrameListener::isExclusive() {
    return false;
}

Input::InputHandler *FrameListener::getInputHandler() {
    return nullptr;
}

}