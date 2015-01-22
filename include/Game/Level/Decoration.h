#ifndef GAME_LEVEL_DECORATION_H_INCLUDED
#define GAME_LEVEL_DECORATION_H_INCLUDED

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <EngineSystem/Video/Render/AnimatedSprite.h>

namespace Level {

    class Decoration : public sf::Drawable {
        public:
            Decoration();
            Decoration(int posX_, int posY_, int scale_, const std::string& id_);
            ~Decoration();

            void update(const sf::Time& timeElapsed);
            void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;

            int getScale() const;
            
        private:
            int posX;
            int posY;
            int scale;
            std::string id;

            Video::Render::Sprite* sprite;

    };

}

#endif