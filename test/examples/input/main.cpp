#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <sstream>

#include <vector>
#include <memory>
#include <EngineSystem/Input/Context.h>
#include <EngineSystem/Input/InputHandler.h>

static std::string statusStr = "Status";

void actionCallback(const char *message) {
    statusStr = std::string("action: ") + message;
}

void stateCallback(bool pressed) {
    statusStr = pressed ? "pressed" : "not pressed";
}

void rangeCallback(float offset) {
    std::ostringstream oss;
    oss << offset;
    statusStr = oss.str();
}

std::string &getInputStatus() {
    
    
    return statusStr;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Example");

    sf::Font font;
    if (!font.loadFromFile("assets/sansation.ttf")) {
        return EXIT_FAILURE;
    }
        
    sf::Text message;
    message.setFont(font);
    message.setCharacterSize(40);
    message.setPosition(170.f, 150.f);
    message.setColor(sf::Color::White);
    message.setString("Example");
    
    sf::Event event;
    
    Input::Context context(true);

    context.addBinding("right", Input::ID::Right);
    context.addBinding("up", Input::ID::Up);
    context.addBinding("run", Input::ID::R);
    context.addBinding("right", Input::ID::GamepadDPadRight); //should be able to do this
    context.addBinding("run", Input::ID::GamepadLeftX);
    context.addBinding("up", Input::ID::GamepadLeftY);

    context.addBinding("slash", Input::ID::GamepadButtonX);
    context.addBinding("slash", Input::ID::X);
    

    context.addAction("right", std::bind(actionCallback,"right"));
    context.addAction("slash", std::bind(actionCallback,"slash"));
    context.addState("up", stateCallback);
    context.addRange("run", rangeCallback);
    

    
    Input::InputHandler::ContextVector contextVector;
    contextVector.push_back(context);
    
    Input::InputHandler inputHandler(contextVector);
    
    while (window.isOpen()) {        
        while (window.pollEvent(event)) {
            // Window closed or escape key pressed: exit
            if ((event.type == sf::Event::Closed) || 
               ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))) {
                window.close();
                break;
            }
            
            std::unique_ptr<Input::Input> input_p(Input::translateEvent(event));
            if(input_p) {
                inputHandler.handleInput(*input_p);
            }
        }
        
        message.setString(getInputStatus());
        
        window.clear(sf::Color(50, 200, 50));
        window.draw(message);
        window.display();
    }
    return EXIT_SUCCESS;
}