#include <EngineSystem/Video/Render/AnimatedSprite.h>

namespace Video {

    namespace Render {

        
        AnimatedSprite::AnimatedSprite() : Sprite() {
            currentFrame = frames.begin();
        }

        AnimatedSprite::AnimatedSprite(sf::Texture& texture_) : Sprite(texture_) {
            currentFrame = frames.begin();
        }

        AnimatedSprite::~AnimatedSprite() {

        }

        void AnimatedSprite::update(const sf::Time& timeElapsed_) {
            sf::Time timeLeft;

            if(frames.size() > 0) {
                timeLeft = getCurrentFrame().update(timeElapsed_);
                if(timeLeft < sf::seconds(0.0f)) {
                    getCurrentFrame().reset();
                    setNextFrame();
                }
            }
        }

        void AnimatedSprite::draw(sf::RenderWindow* windowHandle_) {
            if(frames.size() > 0) {
                sprite.setTextureRect(getCurrentFrame().getTextureSegment());
                setSize(size);

                windowHandle_->draw(sprite);
            }
        }

        void AnimatedSprite::insertFrame(const Sprite::Frame& frame_) {
            frames.push_back(frame_);
        }

        Sprite::Frame& AnimatedSprite::getCurrentFrame() {
            if(currentFrame == frames.end())
                currentFrame = frames.begin();

            return *currentFrame;
        }

        void AnimatedSprite::setNextFrame() {
            ++currentFrame;

            if(currentFrame == frames.end())
                currentFrame = frames.begin();
        }

    }

}