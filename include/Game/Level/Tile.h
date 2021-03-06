#ifndef GAME_LEVEL_TILE_H_INCLUDED
#define GAME_LEVEL_TILE_H_INCLUDED

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <EngineSystem/Video/Render/AnimatedSprite.h>
#include <memory>

namespace Level {

    class Tile : public sf::Drawable {
        public:
            enum class Type {
                Empty,
                Brick,
                Spikes
            };

        public:
            Tile();
            Tile(Type type_);
            virtual ~Tile();

            void update(const sf::Time& timeElapsed);
            void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;

            void setPosition(const sf::Vector2f& position);
            void setType(Type type_);

            Type getType() const;
            const sf::Vector2f& getPosition() const;

            sf::Vector2f getSize() const;

        protected:
            std::shared_ptr<Video::Render::Sprite> sprite;

        private:
            Type type;
    };

}

#endif
