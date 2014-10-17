#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "LibrariesManager.h"
#include "Rendering\Window.h"
#include "InputManager.h"
#include "LogicManager.h"
#include "PhysicsManager.h"
#include "RenderingManager.h"

class Game {
    public:
        // Methods
        static Game& get();
        void init();
        void start();
        void pause();
        void resume();
        void end();

        // Variables
        bool isEnd;

        // Modules
        Rendering::Window&  getWindow();
        LibrariesManager&   getLibrariesManager();
        InputManager&       getInputManager();
        LogicManager&       getLogicManager();
        PhysicsManager&     getPhysicsManager();
        RenderingManager&   getRenderingManager();


    private:
        // Methods
        Game();
        ~Game();

        // Variables

        // Modules
        Rendering::Window*  window;
        LibrariesManager*   librariesManager;
        InputManager*       inputManager;
        LogicManager*       logicManager;
        PhysicsManager*     physicsManager;
        RenderingManager*   renderingManager;
};

#endif