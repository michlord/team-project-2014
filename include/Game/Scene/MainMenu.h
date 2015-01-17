#ifndef GAME_SCENE_MAINMENU_INCLUDED_H
#define GAME_SCENE_MAINMENU_INCLUDED_H

#include <EngineApp/SceneStack.h>
#include <EngineApp/FrameListener.h>
#include <EngineApp/FrameContext.h>

#include <EngineSystem/Assets/AssetsManager.h>

#include <EngineSystem/Input/InputHandler.h>

#include <Game/Menu/List.h>
#include <Game/Menu/ListItem.h>

using namespace Core;

class MainMenu : public FrameListener {
    private:
        Assets::AssetsManager                assets;
        std::unique_ptr<Input::InputHandler> inputHandler;
        std::unique_ptr<Menu::List>          menuList;
    public:
        MainMenu(SceneStack* sceneStack_);
        bool render();
        bool fixedUpdate();
        Input::InputHandler *getInputHandler();
};

#endif // GAME_SCENE_MAINMENU_INCLUDED_H