#include <iostream>
#include <EngineSystem/Video/Render/Sprite.h>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Example");

    sf::Texture texture;
    if(texture.loadFromFile("assets/sprite.png") == false) {
        std::cerr << "Nie zaladowano sprite'u!" << std::endl;
        return 0;
    }

    Video::Render::Sprite sprite;

    sprite.bindTexture(texture);                            // Precyzujemy z ktorej tekstury bedziemy rysowac
                                                            // Zmiana tekstury wymaga ponownej specyfikacji segmentu

    sprite.setTextureSegment(sf::IntRect(0, 0, 150, 120));  // Ustawienie segmentu tekstury, ktory wybieramy z calej tekstury
                                                            // Domyslnie jest to cala tekstura (ale mozemy wyswietlic tylko
                                                            // jej kawalek.

    sprite.setPosition(sf::Vector2f(100.0f, 100.0f));       // Pozycja - mierzona w pikselach od lewego gornego rogu
    sprite.setSize(sf::Vector2u(50, 50));                   // Rozmiar - mierzony w pikselach
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        sprite.draw(&window);                               // Rysujemy nasz sprite na danym oknie

        window.display();
    }

    return 0;
}