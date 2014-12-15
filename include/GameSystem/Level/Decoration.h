#ifndef GAME_SYSTEM_LEVEL_DECORATION_H_INCLUDED
#define GAME_SYSTEM_LEVEL_DECORATION_H_INCLUDED

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <EngineSystem/Video/Render/AnimatedSprite.h>

namespace Level {

    //TODO: work out decoration's data

    class Decoration : public sf::Drawable {
        public:
            Decoration();
            ~Decoration();

            void update(const sf::Time& timeElapsed);
            void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
            
        private:
            Video::Render::Sprite* sprite;

    };

}

#endif