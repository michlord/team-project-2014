#include <EngineApp/EngineApp.h>

int main() {
    Core::EngineApp app;

    app.load();
    app.init();
    app.run();
    app.cleanup();

    return 0;
}