#ifndef ENGINE_SYSTEM_VIDEO_RENDER_SPRITE_H_INCLUDED
#define ENGINE_SYSTEM_VIDEO_RENDER_SPRITE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace Video {

    namespace Render {

        class Sprite {
            public:
                Sprite();
                Sprite(sf::Texture& texture_);
                Sprite(sf::Texture& texture_, const sf::IntRect& textureSegment);

                void draw(sf::RenderWindow* windowHandle_);
                void bindTexture(sf::Texture& texture_);

                void setRotation(float angle_);
                void setSize(const sf::Vector2u& size_);
                void setPosition(const sf::Vector2f& position_);
                void setTextureSegment(const sf::IntRect& segment_);
                void setColorMask(const sf::Color& mask_);
                void movePosition(const sf::Vector2f& moveVector_);
                void setSize(unsigned int width_, unsigned int height_);
                void setPosition(float positionX_, float positionY_);
                void setTextureSegment(int left_, int top_, int width_, int height_);
                void movePosition(float offsetX_, float offsetY_);
                
                float getRotation() const;
                unsigned int getWidth() const;
                unsigned int getHeight() const;
                const sf::Vector2u& getSize() const;
                const sf::Vector2f& getPosition() const;
                const sf::IntRect& getTextureSegment() const;
                const sf::Color& getColorMask() const;

            private:
                float rotation;
                sf::Color colorMask;
                sf::Vector2u size;
                sf::Vector2f position;

                sf::Sprite sprite;
                sf::IntRect textureSegment;
                sf::Texture* texturePtr;
        };

    }

}

#endif