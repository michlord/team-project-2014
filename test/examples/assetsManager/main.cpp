#include <SFML/Graphics/Font.hpp>
#include <EngineSystem/Assets/AssetsManager.h>
#include <EngineSystem/Video/Render/Sprite.h>

int main() {
	using namespace Assets;

	AssetsManager assets;
	assets.loadTexture("assets/no_file.png", "sprite0");	// default placeholder will be assigned to sprite0
	assets.setPlaceholder("assets/placeholder.png");
	assets.loadTexture("assets/no_file.png", "sprite1");	// user placeholder will be assigned to sprite1
	assets.loadTexture("assets/sprite.png", "sprite2");		// sprite1.png will be assigned to sprite2
	assets.setDefaultFont("assets/sansation.ttf");
	assets.loadFont("assets/imagine_font.ttf", "imagine");	// user default font will be assigned to imagine

	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Assets Manager example");
    sf::Clock zegar;
    sf::Time czasKlatki;

	Video::Render::Sprite::Frame frame;
	frame.setTextureSegment(sf::IntRect(0, 0, 100, 100));
	Video::Render::Sprite* sprite[3];

	for(unsigned i = 0 ; i < 3 ; i++) {
		sprite[i] = new Video::Render::Sprite();
		sprite[i]->bindTexture(assets.getTexture("sprite" + std::to_string(i)));
		sprite[i]->setSize(sf::Vector2u(100, 100));
		sprite[i]->setPosition(sf::Vector2f(50.0f + i*150, 50.0f));
		sprite[i]->insertFrame(frame);
	}

	sf::Text text;
	text.setFont(assets.getFont("imagine"));
	text.setCharacterSize(24);
	text.setString("Assets manager test");
	text.setPosition(50, 250);
	text.setColor(sf::Color::White);

    zegar.restart();
    while (window.isOpen()) {
        czasKlatki = zegar.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
		
		window.clear(sf::Color::Green);

		for(auto s : sprite) {
			s->update(czasKlatki);
			s->draw(&window);     
		}
		window.draw(text);
		
		window.display();
    }
}