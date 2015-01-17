#ifndef GAME_LEVEL_DECORATION_H_INCLUDED
#define GAME_LEVEL_DECORATION_H_INCLUDED

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <EngineSystem/Video/Render/AnimatedSprite.h>

namespace Level {

    class Decoration : public sf::Drawable {
        public:
            Decoration();
            Decoration(int posX_, int posY_, int level_, const std::string& id_);
            ~Decoration();

            void update(const sf::Time& timeElapsed);
            void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;

            int getLevel() const;
            
        private:
            int posX;
            int posY;
            int level;
            std::string id;

            Video::Render::Sprite* sprite;

    };

}

#endif