#include <EngineSystem/Input/Input.h>
#include <EngineSystem/Input/AxisInput.h>
#include <EngineSystem/Input/BinaryInput.h>
#include <EngineSystem/Input/InputHandler.h>
#include <SFML/Window.hpp>
#include <array>

namespace Input {

InputHandler::InputHandler(ContextVector contexts_)
    : contexts(contexts_)
{
}

void InputHandler::handleInput(const Input& input) {
    for(auto it = contexts.begin(); it != contexts.end(); ++it) {
        if(it->isActive()) {
            bool res = it->handleInput(input);
            if(res == true) {
                break;
            }
        }
    }
}

void InputHandler::update() {
    for(auto it = contexts.begin(); it != contexts.end(); ++it) {
        if(it->isActive()) {
            bool res = it->update();
            if(res == true) {
                break;
            }
        }
    }
}

namespace {
    ID mapSFMLJoystickButtonToID(unsigned int button) {
        static ID map[] = {
            GamepadButtonX,
            GamepadButtonA,
            GamepadButtonB,
            GamepadButtonY,
            GamepadButtonLB,
            GamepadButtonRB,
            GamepadButtonLT,
            GamepadButtonRT,
            GamepadSelect,
            GamepadStart
        };
        if(button > sizeof(ID)*sizeof(map)) {
            return ID::Unknown;
        }
        return map[button];
    }
}

namespace {
    std::array<bool, sf::Keyboard::KeyCount> keyState;
    bool initKeyState() {
        keyState.fill(false);
        return true;
    }
    bool b = initKeyState();
}



Input *translateEvent(const sf::Event& e) {
    Input *input   = nullptr;
    ID     inputId = ID::Unknown;
    if(e.type == sf::Event::KeyReleased) {
        keyState[e.key.code] = false;
    }
    if(e.type == sf::Event::KeyPressed && !keyState[e.key.code]) {
        keyState[e.key.code] = true;
        inputId = (ID) e.key.code;
        input = new BinaryInput(inputId, true);
    } else if (e.type == sf::Event::KeyReleased) {
        inputId = (ID) e.key.code;
        input = new BinaryInput(inputId, false);
    } else if (e.type == sf::Event::JoystickButtonPressed) {
        inputId = mapSFMLJoystickButtonToID(e.joystickButton.button);
        input = new BinaryInput(inputId, true);
    } else if (e.type == sf::Event::JoystickButtonReleased) {
        inputId = mapSFMLJoystickButtonToID(e.joystickButton.button);
        input = new BinaryInput(inputId, false);
    } else if (e.type == sf::Event::JoystickMoved) {
        switch(e.joystickMove.axis) {
            case sf::Joystick::Axis::X :
                inputId = ID::GamepadLeftX;
                input = new AxisInput(inputId, e.joystickMove.position / 100.0f);
                break;
            case sf::Joystick::Axis::Y :
                inputId = ID::GamepadLeftY;
                input = new AxisInput(inputId, e.joystickMove.position / 100.0f);
                break;
            case sf::Joystick::Axis::Z :
                inputId = ID::GamepadRightX;
                input = new AxisInput(inputId, e.joystickMove.position / 100.0f);
                break;
            case sf::Joystick::Axis::R :
                inputId = ID::GamepadRightY;
                input = new AxisInput(inputId, e.joystickMove.position / 100.0f);
                break;
            case sf::Joystick::Axis::PovY :
                inputId = e.joystickMove.position > 0.0f ? ID::GamepadDPadRight : ID::GamepadDPadLeft;
                input = new BinaryInput(inputId, fabs(e.joystickMove.position / 100.0f) > 0.1f);
                break;
            case sf::Joystick::Axis::PovX :
                inputId = e.joystickMove.position > 0.0f ? ID::GamepadDPadUp : ID::GamepadDPadDown;
                input = new BinaryInput(inputId, fabs(e.joystickMove.position / 100.0f) > 0.1f);
                break;
            default:
                inputId = ID::Unknown;
        }
        
    }
    
    return input;
}

}