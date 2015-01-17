#ifndef ENGINE_SYSTEM_INPUT_INPUT_HANDLER_H_INCLUDED
#define ENGINE_SYSTEM_INPUT_INPUT_HANDLER_H_INCLUDED

#include <EngineSystem/Input/Context.h>
#include <SFML/Window.hpp>
#include <functional>

namespace Input {

class InputHandler {
    public:
        typedef std::vector< Context > ContextVector;
        typedef std::vector< std::function<void(const Input&)> > ForwardTargetVector;
    private:
        ContextVector       contexts;
        ForwardTargetVector inputForwardingTargets;
    public:
        InputHandler(ContextVector contexts_);
        void handleInput(const Input& input);
        void update();
        void addInputForwardingTarget(std::function<void(const Input&)> target);
};

Input *translateEvent(const sf::Event& e);

}

#endif // ENGINE_SYSTEM_INPUT_INPUT_HANDLER_H_INCLUDED
