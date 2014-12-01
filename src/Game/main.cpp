#include <EngineApp/EngineApp.h>
#include <EngineApp/FrameContext.h>
#include <Game/Scene/Intro.h>

int main() {
    Core::EngineApp app;

    app.load();
    app.init();
    app.pushInitialScene(new Scene::Intro(Core::frameContext.sceneStack.get()));
    app.run();
    app.cleanup();

    return 0;
}