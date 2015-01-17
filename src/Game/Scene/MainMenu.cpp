#include <Game/Scene/MainMenu.h>
#include <functional>



MainMenu::MainMenu(SceneStack* sceneStack_)
 : FrameListener(sceneStack_)
{
    assets.loadFont("assets/fonts/Munro.ttf", "headline_font");
    menuList.reset(new Menu::List(&assets.getFont("headline_font")));
    Menu::ListItem item1(menuList.get(), "Start game");
    Menu::ListItem item2(menuList.get(), "Options");
    Menu::ListItem item3(menuList.get(), "Exit");
    
    Input::InputHandler::ContextVector contextVector;
    inputHandler.reset(new Input::InputHandler(contextVector));
    //inputHandler has to forward input to menu instance
    inputHandler->addInputForwardingTarget(std::bind(&Menu::List::handleInput, menuList.get(), std::placeholders::_1));
}

bool MainMenu::render() {
    Core::frameContext.window->draw(*menuList);
    return true;
}

bool MainMenu::fixedUpdate() {
    
    return true;
}

Input::InputHandler *MainMenu::getInputHandler() {
    return inputHandler.get();
}