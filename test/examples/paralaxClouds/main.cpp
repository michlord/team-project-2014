#include <EngineApp/EngineApp.h>
#include <EngineApp/FrameContext.h>
#include "Scene.h"

int main() {
    Core::EngineApp app;

    app.load();
    app.init();
    app.pushInitialScene(new Scene(Core::frameContext.sceneStack.get()));
    app.run();
    app.cleanup();

    return 0;
}