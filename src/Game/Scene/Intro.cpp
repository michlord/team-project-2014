#include <Game/Scene/Intro.h>

using namespace Core;

namespace Scene {

Intro::Intro(SceneStack* sceneStack_)
 : FrameListener(sceneStack_)
{
}

void Intro::render() {

}

void Intro::fixedUpdate() {

}

bool Intro::isExclusive() {
    return true;
}

}