#include <EngineApp/EngineApp.h>
#include <EngineApp/FrameContext.h>
#include "GameplayScene.h"

int main() {
    Core::EngineApp app;

    app.load();
    app.init();
    app.pushInitialScene(new Gameplay(Core::frameContext.sceneStack.get()));
    app.run();
    app.cleanup();

    return 0;
}