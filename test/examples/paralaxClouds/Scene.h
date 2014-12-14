#ifndef TEST_PARALAX_CLOUDS_SCENE_H_INCLUDED
#define TEST_PARALAX_CLOUDS_SCENE_H_INCLUDED

#include <EngineApp/SceneStack.h>
#include <EngineApp/FrameListener.h>
#include <EngineApp/FrameContext.h>
#include <EngineSystem/Input/InputHandler.h>

#include <EngineSystem/Assets/AssetsManager.h>

#include <memory>
#include <array>
#include <vector>

#include <SFML/Graphics.hpp>

using namespace Core;
using namespace Assets;

class Scene : public FrameListener {
    private:    
        AssetsManager assets;
        std::unique_ptr<Input::InputHandler> inputHandler;
        void initInputHandler();
        void initLayers();
        sf::Vector2f cameraCenter;
        void moveCamera(sf::Vector2f direction);
        std::array< std::vector<sf::Sprite>, 3 > layers;
        std::array<float, 3> layersScales;
    public:
        Scene(SceneStack* sceneStack_);
        bool render();
        bool fixedUpdate();
        Input::InputHandler *getInputHandler();
};


#endif // TEST_PARALAX_CLOUDS_SCENE_H_INCLUDED