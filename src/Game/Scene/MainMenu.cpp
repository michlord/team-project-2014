#include <Game/Scene/MainMenu.h>
#include <functional>
#include <string>
#include <EngineSystem/Input/Translation.h>
#include <EngineSystem/Config/Config.h>

namespace Scene {

MainMenu::MainMenu(SceneStack* sceneStack_)
 : FrameListener(sceneStack_)
{
    assets.loadFont("assets/fonts/Munro.ttf", "headline_font");

    {
        menuList[MenuType::Menu].reset(new Menu::List(&assets.getFont("headline_font")));

        Menu::ListItem item1(menuList[MenuType::Menu].get(), "Start game", 0, false,
            [this](const Input::Input& in, int val){
                (void) in;
                popScene();
                pushScene(new Gameplay(sceneStack, 0));
                return val;
            }
        );
        Menu::ListItem item2(menuList[MenuType::Menu].get(), "Options", 0, false, [this](const Input::Input& in, int val) { (void) in; curMenu = MenuType::Options; return val; });
        Menu::ListItem item3(menuList[MenuType::Menu].get(), "Exit", 0, false, [](const Input::Input& in, int val) { (void) in; Core::frameContext.appWindow->close(); return val; });
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

        Config &cfg = Config::Get();
        cfg.load("assets/config.ini");

        Menu::ListItem item1(menuList[MenuType::Options].get(), "UP:", cfg.getInt("keys", "up", -1), true, setKeyFun, dispKeyFun);
        Menu::ListItem item2(menuList[MenuType::Options].get(), "LEFT:", cfg.getInt("keys", "left", -1), true, setKeyFun, dispKeyFun);
        Menu::ListItem item3(menuList[MenuType::Options].get(), "RIGHT:", cfg.getInt("keys", "right", -1), true, setKeyFun, dispKeyFun);
        Menu::ListItem item4(menuList[MenuType::Options].get(), "DOWN:", cfg.getInt("keys", "down", -1), true, setKeyFun, dispKeyFun);
        Menu::ListItem item5(menuList[MenuType::Options].get(), "JUMP:", cfg.getInt("keys", "jump", -1), true, setKeyFun, dispKeyFun);
        Menu::ListItem item6(menuList[MenuType::Options].get(), "SLASH:", cfg.getInt("keys", "slash", -1), true, setKeyFun, dispKeyFun);
        Menu::ListItem item7(menuList[MenuType::Options].get(), "MAGIC:", cfg.getInt("keys", "magic", -1), true, setKeyFun, dispKeyFun);
        Menu::ListItem item10(menuList[MenuType::Options].get(), "Back", false, 0,
            [this](const Input::Input& in, int val) {
                (void) in;
                Config &cfg = Config::Get();
                auto& vec = menuList[MenuType::Options]->getStore();
                cfg.set("keys", "up", std::to_string(vec[0].getValue()));
                cfg.set("keys", "left", std::to_string(vec[1].getValue()));
                cfg.set("keys", "right", std::to_string(vec[2].getValue()));
                cfg.set("keys", "down", std::to_string(vec[3].getValue()));
                cfg.set("keys", "jump", std::to_string(vec[4].getValue()));
                cfg.set("keys", "slash", std::to_string(vec[5].getValue()));
                cfg.set("keys", "magic", std::to_string(vec[6].getValue()));

                cfg.save("assets/config.ini");
                curMenu = MenuType::Menu;
                return val;
            }
        );
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

}
