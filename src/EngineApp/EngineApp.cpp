#include <EngineApp/EngineApp.h>
#include <EngineApp/WindowContext.h>

EngineApp::EngineApp() {
    window = new WindowContext();
}

EngineApp::~EngineApp() {
    delete window;
}

void EngineApp::load() {

}

void EngineApp::init() {
    getWindow().setTitle("Rage mage");
    getWindow().setPosition(100, 100);
    getWindow().setSize(800, 600);
    getWindow().setVsync(true); // override by graphic's drivers possible!
    getWindow().open();
}

void EngineApp::run() {
    sf::Event event;
    sf::Time frameTime;
    sf::Time timeAccumulator;
    sf::Time deltaTime = sf::seconds(1.0f / 120.0f); // 120Hz update rate

    while(getWindow().isOpened()) {
        getWindow().update();

        while(getWindow().getHandle().pollEvent(event))
            dispatchEvent(event);
        
        frameTime = getWindow().getFrameTime();
        timeAccumulator += frameTime;
        while (timeAccumulator >= deltaTime) {
            // updateSomething(deltaTime);

            timeAccumulator -= deltaTime;
        }

        // renderSomething(getWindow().getHandle());
    }
}

void EngineApp::cleanup() {

}

WindowContext& EngineApp::getWindow() {
    return *window;
}

void EngineApp::dispatchEvent(const sf::Event& event) {
    // Temporary function to be replaced by state machine
    if(event.type == sf::Event::Closed)
        getWindow().close();
}