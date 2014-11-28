#include <iostream>
#include <functional>

#include <EngineSystem/Video/Render/Sprite.h>
#include <EngineSystem/Video/Render/AnimatedSprite.h>
#include <EngineSystem/Video/Render/Animation.h>

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
    sprite->setPosition(sf::Vector2f(200.0f, 200.0f));              // ustawienie pozycji na ekranie
    sprite->setSize(sf::Vector2u(100, 100));                        // ustawienie rozmiaru na ekranie

}

void przygotujAnimacje(Video::Render::Animation* animation, sf::Texture& tekstura) {
    Video::Render::AnimatedSprite sequence[2];
    Video::Render::Sprite::Frame frames[6];

    frames[0].setTextureSegment(sf::IntRect(0, 0, 150, 120));       // przypisanie segmentu klatki #1 sekwencji #1
    frames[1].setTextureSegment(sf::IntRect(100, 0, 250, 120));     // przypisanie segmentu klatki #2 sekwencji #1
    frames[2].setTextureSegment(sf::IntRect(0, 150, 150, 256));     // przypisanie segmentu klatki #3 sekwencji #1

    frames[3].setTextureSegment(sf::IntRect(0, 0, 150, 120));       // przypisanie segmentu klatki #1 sekwencji #2
    frames[4].setTextureSegment(sf::IntRect(100, 0, 250, 120));     // przypisanie segmentu klatki #2 sekwencji #2
    frames[5].setTextureSegment(sf::IntRect(0, 150, 150, 256));     // przypisanie segmentu klatki #3 sekwnecji #2

    for(int i = 0; i < 6; ++i) {
        frames[i].setDuration(sf::seconds(0.5f));                   // ustawienie czasu trwania klatki na 0.5s

        if(i < 3)
            sequence[0].insertFrame(frames[i]);                     // klatki 0-2 dodane sa do pierwszej sekwencji
        else
            sequence[1].insertFrame(frames[i]);                     // klatki 0-3 dodane sa do drugiej sekwencji
    }

    sequence[0].bindTexture(tekstura);                              // ustawienie tekstury
    sequence[0].setPosition(sf::Vector2f(400.0f, 200.0f));          // ustawienie pozycji na ekranie
    sequence[0].setSize(sf::Vector2u(100, 100));                    // ustawienie rozmiaru na ekranie
    sequence[0].setColorMask(sf::Color(0, 255, 0, 255));            // ustawienie maski koloru dla sekwencji #2

    sequence[1].bindTexture(tekstura);                              // ustawienie tekstury
    sequence[1].setPosition(sf::Vector2f(400.0f, 200.0f));          // ustawienie pozycji na ekranie
    sequence[1].setSize(sf::Vector2u(100, 100));                    // ustawienie rozmiaru na ekranie
    sequence[1].setColorMask(sf::Color(255, 0, 0, 255));            // ustawienie maski koloru dla sekwencji #2

    auto function = [animation]() {                                 // funkcja lambda, ktora zachowuje wskaznik na animacje
        animation->setCurrentSequence("sekwencja1");                // i przy wykonaniu ustawia aktualna sekwnecje na #1
        std::cout << "Sequence #2 is finished!" << std::endl;       // 
    };

    animation->addSequence("sekwencja1", sequence[0], "sekwencja2");// dodanie sekwnecji #1, ustawienie nastepnej sekwencji na #2


    animation->addSequence("sekwencja2", sequence[1], function);    // dodanie sekwencji #2, ustawienie funkcji, ktora
                                                                    // zostanie wykonana po zakonczeniu sekwencji #2 i 
                                                                    // zmieni sekwencje na #1
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

    /**
     * Sprite i AnimatedSprite
     */
    Video::Render::Sprite* sprites[2];


    sprites[0] = new Video::Render::Sprite();
    sprites[1] = new Video::Render::AnimatedSprite();

    przygotujSprite(sprites[0], texture);
    przygotujAnimowanySprite(sprites[1], texture);


    /**
     * Animacja
     */
    Video::Render::Animation animation;                                 // Tworzymy animacje
    przygotujAnimacje(&animation, texture);                             // Ustawiamy animacje dodajac do niej sekwencje
    animation.setCurrentSequence("sekwencja2");                         // Wybieramy ktora sekwencja jest aktualna

    /**
     * Petla aplikacji
     */
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

        animation.update(czasKlatki);                           // Aktualizujemy aktualna sekwencje animacji
        animation.draw(&window);                                // Rysujemy aktualna sekwencje animacji

        window.display();
    }

    delete sprites[0];
    delete sprites[1];

    return 0;
}