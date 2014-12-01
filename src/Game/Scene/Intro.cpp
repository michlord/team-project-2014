#include <Game/Scene/Intro.h>

using namespace Core;

namespace Scene {

Intro::Intro(SceneStack* sceneStack_)
 : FrameListener(sceneStack_)
{
}

bool Intro::render() {
    return true;
}

bool Intro::fixedUpdate() {
    return true;
}

}