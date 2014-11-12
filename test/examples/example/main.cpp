#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "util.h"

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
    
    while (window.isOpen()) {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Window closed or escape key pressed: exit
            if ((event.type == sf::Event::Closed) || 
               ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))) {
                window.close();
                break;
            }
        }
        message.setString(randomString());
        
        window.clear(sf::Color(50, 200, 50));
        window.draw(message);
        window.display();
    }
    return EXIT_SUCCESS;
}