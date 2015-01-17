#include <Game/Scene/MainMenu.h>
#include <functional>
#include <string>
#include <EngineSystem/Input/Translation.h>


MainMenu::MainMenu(SceneStack* sceneStack_)
 : FrameListener(sceneStack_)
{
    assets.loadFont("assets/fonts/Munro.ttf", "headline_font");
    
    {
        menuList[MenuType::Menu].reset(new Menu::List(&assets.getFont("headline_font")));
        
        Menu::ListItem item1(menuList[MenuType::Menu].get(), "Start game");
        Menu::ListItem item2(menuList[MenuType::Menu].get(), "Options", false, [this](const Input::Input& in, int val) { (void) in; curMenu = MenuType::Options; return val; });
        Menu::ListItem item3(menuList[MenuType::Menu].get(), "Exit", false, [](const Input::Input& in, int val) { (void) in; Core::frameContext.appWindow->close(); return val; });
    }
    
    {
        menuList[MenuType::Options].reset(new Menu::List(&assets.getFont("headline_font")));
        
        auto setKeyFun = [](const Input::Input& in, int val) {
            (void) val;
            return (int) in.getId();
        };
        
        auto dispKeyFun = [](int val) {
            return Input::to_string((Input::ID) val);
        };
        
        Menu::ListItem item1(menuList[MenuType::Options].get(), "Key UP:", true, setKeyFun, dispKeyFun);
        Menu::ListItem item2(menuList[MenuType::Options].get(), "Key LEFT:", true, setKeyFun, dispKeyFun);
        Menu::ListItem item3(menuList[MenuType::Options].get(), "Key RIGHT:", true, setKeyFun, dispKeyFun);
        Menu::ListItem item4(menuList[MenuType::Options].get(), "Key DOWN:", true, setKeyFun, dispKeyFun);
        Menu::ListItem item5(menuList[MenuType::Options].get(), "Key JUMP:", true, setKeyFun, dispKeyFun);
        Menu::ListItem item6(menuList[MenuType::Options].get(), "Key SLASH:", true, setKeyFun, dispKeyFun);
        Menu::ListItem item7(menuList[MenuType::Options].get(), "Key MAGIC:", true, setKeyFun, dispKeyFun);
        
        Menu::ListItem item10(menuList[MenuType::Options].get(), "Back", false, [this](const Input::Input& in, int val) { (void) in; curMenu = MenuType::Menu; return val; });
    }
    
    {
        menuList[MenuType::LevelSelect].reset(new Menu::List(&assets.getFont("headline_font")));
    }
    
    curMenu = MenuType::Menu;
    
    Input::InputHandler::ContextVector contextVector;
    inputHandler.reset(new Input::InputHandler(contextVector));
    //inputHandler has to forward input to menu instance
    inputHandler->addInputForwardingTarget(std::bind(&MainMenu::handleListInputs, this, std::placeholders::_1));
}

void MainMenu::handleListInputs(const Input::Input &in) {
    menuList[curMenu]->handleInput(in);
}

bool MainMenu::render() {
    Core::frameContext.window->draw(*menuList[curMenu]);
    return true;
}

bool MainMenu::fixedUpdate() {
    
    return true;
}

Input::InputHandler *MainMenu::getInputHandler() {
    return inputHandler.get();
}