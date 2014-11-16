#ifndef ENGINE_SYSTEM_INPUT_INPUT_HANDLER_H_INCLUDED
#define ENGINE_SYSTEM_INPUT_INPUT_HANDLER_H_INCLUDED

#include <EngineSystem/Input/Context.h>
#include <SFML/Window.hpp>

namespace INPUT {

class InputHandler {
    public:
        typedef std::vector< Context > ContextVector;
    private:
        ContextVector contexts;
    public:
        InputHandler(ContextVector contexts_);
        void handleInput(const Input& input);
};

Input *translateEvent(const sf::Event& e);

}

#endif // ENGINE_SYSTEM_INPUT_INPUT_HANDLER_H_INCLUDED
