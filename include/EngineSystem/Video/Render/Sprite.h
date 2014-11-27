#ifndef ENGINE_SYSTEM_VIDEO_RENDER_SPRITE_H_INCLUDED
#define ENGINE_SYSTEM_VIDEO_RENDER_SPRITE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace Video {

    namespace Render {

        class Sprite : sf::Drawable {
            public:
                class Frame {
                    public:
                        Frame();
                        Frame(const sf::IntRect& textureSegment_, const sf::Time& duration_);

                        void reset();
                        const sf::Time& update(const sf::Time& timeElapsed_);
                        
                        void setDuration(const sf::Time& time_);
                        void setTextureSegment(const sf::IntRect& textureSegment_);

                        const sf::Time& getTimeLeft() const;
                        const sf::Time& getDuration() const;
                        const sf::IntRect& getTextureSegment() const;

                    private:
                        void setTimeLeft(const sf::Time& time);

                        sf::Time timeLeft;
                        sf::Time duration;
                        sf::IntRect textureSegment;
                };


            public:
                Sprite();
                Sprite(sf::Texture& texture_);
                Sprite(sf::Texture& texture_, const Sprite::Frame& frame_);
                virtual ~Sprite();

                virtual void update(const sf::Time& timeElapsed_);
                virtual void draw(sf::RenderWindow* windowHandle_) const;
                virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
                virtual void insertFrame(const Sprite::Frame& frame_);
                void bindTexture(sf::Texture& texture_);

                void setRotation(float angle_);
                void setSize(const sf::Vector2u& size_);
                void setSize(unsigned int width_, unsigned int height_);
                void setPosition(const sf::Vector2f& position_);
                void setPosition(float positionX_, float positionY_);
                void setColorMask(const sf::Color& mask_);

                void movePosition(const sf::Vector2f& moveVector_);
                void movePosition(float offsetX_, float offsetY_);
                
                float getRotation() const;
                unsigned int getFrameCount() const;
                unsigned int getWidth() const;
                unsigned int getHeight() const;
                const sf::Vector2u& getSize() const;
                const sf::Vector2f& getPosition() const;
                const sf::Color& getColorMask() const;
                const Sprite::Frame* getFrames() const;

            protected:
                bool isTextureBinded;
                bool isTextureBindedWarningPrinted;
                bool isNullWindowWarningPrinted;

                unsigned int frameCount;
                float rotation;
                sf::Color colorMask;
                sf::Vector2u size;
                sf::Vector2f position;

                sf::Sprite sprite;
                sf::Texture* texturePtr;

            private:
                Sprite::Frame frame;    // private since in animated sprite there will be an array of frames

        };

    }

}

#endif