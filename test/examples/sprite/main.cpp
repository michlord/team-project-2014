#include <iostream>
#include <EngineSystem/Video/Render/Sprite.h>
#include <EngineSystem/Video/Render/AnimatedSprite.h>

void przygotujSprite(Video::Render::Sprite* sprite, sf::Texture& tekstura) {
    Video::Render::Sprite::Frame frame;

    frame.setTextureSegment(sf::IntRect(0, 0, 150, 120));           // Ustawienie wycinka tekstury jako 'zrodla' dla segmentu klatki
    sprite->insertFrame(frame);                                     // Dodanie klatki do sprite'a. Jako ze jest to Sprite, nie
                                                                    // AnimatedSprite, kazde dodanie klatki nadpisuje nastepne
    sprite->bindTexture(tekstura);                                  // Precyzujemy z ktorej tekstury bedziemy rysowac
                                                                    // Zmiana tekstury wymaga ponownej specyfikacji segmentu
    sprite->setPosition(sf::Vector2f(100.0f, 100.0f));              // Pozycja - mierzona w pikselach od lewego gornego rogu
    sprite->setSize(sf::Vector2u(50, 50));                          // Rozmiar - mierzony w pikselach
}

void przygotujAnimowanySprite(Video::Render::Sprite* sprite, sf::Texture& tekstura) {
    Video::Render::Sprite::Frame frames[3];

    frames[0].setTextureSegment(sf::IntRect(0, 0, 150, 120));       // przypisanie segmentu klatki #1
    frames[1].setTextureSegment(sf::IntRect(100, 0, 250, 120));     // przypisanie segmentu klatki #2
    frames[2].setTextureSegment(sf::IntRect(0, 150, 150, 256));     // przypisanie segmentu klatki #3

    for(auto frame : frames) {
        frame.setDuration(sf::seconds(0.5f));                       // ustawienie czasu trwania danej klatki na 0.5s
        sprite->insertFrame(frame);                                 // dodanie klatki do obiektu
    }

    sprite->bindTexture(tekstura);                                  // ustawienie tekstury
    sprite->setPosition(sf::Vector2f(300.0f, 300.0f));              // ustawienie pozycji na ekranie
    sprite->setSize(sf::Vector2u(100, 100));                        // ustawienie rozmiaru na ekranie

}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Example");
    sf::Clock zegar;
    sf::Time czasKlatki;

    sf::Texture texture;
    if(texture.loadFromFile("assets/sprite.png") == false) {
        std::cerr << "Nie zaladowano sprite'u!" << std::endl;
        return 0;
    }

    Video::Render::Sprite* sprites[2];

    sprites[0] = new Video::Render::Sprite();
    sprites[1] = new Video::Render::AnimatedSprite();

    przygotujSprite(sprites[0], texture);
    przygotujAnimowanySprite(sprites[1], texture);

    zegar.restart();
    while (window.isOpen()) {
        czasKlatki = zegar.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        for(Video::Render::Sprite* sprite : sprites) {
            sprite->update(czasKlatki);                         // Aktualizujemy sprite wzgledem czasu, ktory minal 
            sprite->draw(&window);                              // Rysujemy nasz sprite na danym oknie
        }

        window.display();
    }

    return 0;
}