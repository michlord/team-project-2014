#ifndef ENGINEAPP_H_INCLUDED
#define ENGINEAPP_H_INCLUDED

#include "WindowContext.h"

namespace Core {

class FrameListener;

class EngineApp {
    public:
        EngineApp();
        ~EngineApp();

        void load();
        void init();
        void pushInitialScene(FrameListener* scene);
        void run();
        void cleanup();

        WindowContext& getWindow();

    private:
        void dispatchEvent(const sf::Event& event);

        WindowContext* window;
        
    
};

}

#endif