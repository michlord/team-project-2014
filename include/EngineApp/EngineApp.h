#ifndef ENGINEAPP_H_INCLUDED
#define ENGINEAPP_H_INCLUDED

#include "WindowContext.h"

namespace Core {

class EngineApp {
    public:
        EngineApp();
        ~EngineApp();

        void load();
        void init();
        void run();
        void cleanup();

        WindowContext& getWindow();

    private:
        void dispatchEvent(const sf::Event& event);

        WindowContext* window;
    
};

}

#endif