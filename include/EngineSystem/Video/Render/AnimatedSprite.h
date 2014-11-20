#ifndef ENGINE_SYSTEM_VIDEO_RENDER_ANIMATEDSPRITE_H_INCLUDED
#define ENGINE_SYSTEM_VIDEO_RENDER_ANIMATEDSPRITE_H_INCLUDED

#include <EngineSystem/Video/Render/Sprite.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace Video {

    namespace Render {

        class AnimatedSprite : public Sprite {
            public:
                AnimatedSprite();
                AnimatedSprite(sf::Texture& texture_);
                virtual ~AnimatedSprite();

                virtual void update(const sf::Time& timeElapsed_);
                virtual void draw(sf::RenderWindow* windowHandle_);
                virtual void insertFrame(const Sprite::Frame& frame_);

            private:
                Sprite::Frame& getCurrentFrame();
                void setNextFrame();

                std::vector<Sprite::Frame>::iterator currentFrame;
                std::vector<Sprite::Frame> frames;    // private since in animated sprite there will be an array of frames

        };

    }

}

#endif