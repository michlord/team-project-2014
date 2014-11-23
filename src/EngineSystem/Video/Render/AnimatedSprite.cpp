#include <EngineSystem/Video/Render/AnimatedSprite.h>

namespace Video {

    namespace Render {

        
        AnimatedSprite::AnimatedSprite() : Sprite() {
            currentFrame = 0;
        }

        AnimatedSprite::AnimatedSprite(sf::Texture& texture_) : Sprite(texture_) {
            currentFrame = 0;
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
                sprite.setTextureRect(getCurrentFrame().getTextureSegment());
                setSize(size);
            }
        }

        void AnimatedSprite::draw(sf::RenderWindow* windowHandle_) const {
            if(frames.size() > 0)
                windowHandle_->draw(sprite);
        }

        void AnimatedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const {
            if(frames.size() > 0)
                target.draw(sprite, states);
        }

        void AnimatedSprite::insertFrame(const Sprite::Frame& frame_) {
            frames.push_back(frame_);
        }

        Sprite::Frame& AnimatedSprite::getCurrentFrame() {
            return frames.at(currentFrame);
        }

        void AnimatedSprite::setNextFrame() {
            ++currentFrame;

            if(currentFrame == frames.size())
                currentFrame = 0;
        }

    }

}