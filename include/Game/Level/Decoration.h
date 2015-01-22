#ifndef GAME_LEVEL_DECORATION_H_INCLUDED
#define GAME_LEVEL_DECORATION_H_INCLUDED

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <EngineSystem/Video/Render/AnimatedSprite.h>

#include <memory>

namespace Level {

    class Decoration : public sf::Drawable {
        public:
            Decoration();
            Decoration(float posX_, float posY_, float scale_, const std::string& id_);
            ~Decoration();

            void setup();

            void update(const sf::Time& timeElapsed);
            void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;

            float getScale() const;
            
        private:
            float posX;
            float posY;
            float scale;
            std::string id;
            
            std::shared_ptr<Video::Render::Sprite> sprite;

    };

}

#endif