#include <EngineApp/EngineApp.h>
#include <EngineApp/WindowContext.h>
#include <EngineApp/FrameContext.h>
#include <EngineApp/FrameListener.h>
#include <EngineApp/SceneStack.h>
#include <EngineSystem/Log/Log.h>
#include <EngineSystem/Entity/MessageDispatcher.h>

namespace Core {

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
    getWindow().getHandle().setKeyRepeatEnabled(false);
    getWindow().open();
}

void EngineApp::pushInitialScene(FrameListener* scene) {
    frameContext.sceneStack->pushScene(scene);
    frameContext.sceneStack->applyPendingChanges();
}

void EngineApp::run() {
    sf::Event event;
    sf::Time frameTime;
    sf::Time timeAccumulator;
    sf::Time deltaTime = sf::seconds(1.0f / 120.0f); // 120Hz update rate
    
    frameContext.appWindow = &getWindow();
    frameContext.window = &getWindow().getHandle();
    frameContext.deltaTime = deltaTime.asSeconds();

    while(getWindow().isOpened()) {
        if(frameContext.sceneStack->isEmpty()) {
            Log::get().write(Log::System::Engine, "[Game loop] Scene stack is empty");
            return;
        }
        
        getWindow().update();

        frameTime = getWindow().getFrameTime();
        frameContext.frameTime = frameTime.asSeconds();
        timeAccumulator += frameTime;
        
        while(getWindow().getHandle().pollEvent(event)) {
            dispatchEvent(event);
        }
        
        Entity::MessageDispatcher::getInstance().dispatchMessages();
        
        while (timeAccumulator >= deltaTime) {
            frameContext.sceneStack->fixedUpdate();
            timeAccumulator -= deltaTime;
        }
        getWindow().clear();
        frameContext.sceneStack->render();
        frameContext.sceneStack->applyPendingChanges();
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
    
    frameContext.sceneStack->handleEvent(event);
}

}