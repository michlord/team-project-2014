#include "GameplayScene.h"

Gameplay::Gameplay(SceneStack* sceneStack_)
 : FrameListener(sceneStack_)
{

}

bool Gameplay::render() {
    return true;
}

bool Gameplay::fixedUpdate() {
    return true;
}