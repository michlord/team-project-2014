#include <Game/Scene/Intro.h>
#include <EngineApp/FrameContext.h>


using namespace Core;

namespace Scene {

Intro::Intro(SceneStack* sceneStack_)
 : FrameListener(sceneStack_)
{
    assets.loadFont("assets/fonts/Munro.ttf", "headline_font");
    headlineText.setFont(assets.getFont("headline_font"));
    headlineText.setString("PRESS ENTER TO START RAGEMAGE");
    
    Input::Context context(true);
    context.addBinding("start", Input::ID::Return);
    context.addAction("start", std::bind([this](){
        popScene(); 
        pushScene(new MainMenu(sceneStack));
    }));
    
    Input::InputHandler::ContextVector contextVector;
    contextVector.push_back(context);
    inputHandler.reset(new Input::InputHandler(contextVector));
}

void Intro::setCustomMessage(std::string customMessage = "") {
    headlineText.setString(customMessage + "PRESS ENTER TO START RAGEMAGE");
}

bool Intro::render() {
    Core::frameContext.window->draw(headlineText);
    return true;
}

bool Intro::fixedUpdate() {
    return true;
}

Input::InputHandler *Intro::getInputHandler() {
    return inputHandler.get();
}

}