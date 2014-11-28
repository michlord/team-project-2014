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
                AnimatedSprite(const sf::Texture& texture_);
                AnimatedSprite(const AnimatedSprite& animatedSprite_);
                virtual ~AnimatedSprite();

                virtual void update(const sf::Time& timeElapsed_);
                virtual void draw(sf::RenderWindow* windowHandle_) const;
                virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
                virtual void insertFrame(const Sprite::Frame& frame_);
                virtual void resetCurrentFrame();
                
                void resetFinished();
                void setRepeat(bool flag = true);

                bool isFinished() const;

            private:
                bool finished;
                bool repeat;

                Sprite::Frame& getCurrentFrame();
                void setNextFrame();

                bool isEmptyFramesWarningPrinted;
                unsigned int currentFrame;
                std::vector<Sprite::Frame> frames;    // private since in animated sprite there will be an array of frames
        };

    }

}

#endif