#include <EngineSystem/Video/Render/AnimatedSprite.h>
#include <EngineSystem/Log/Log.h>

namespace Video {

    namespace Render {

        
        AnimatedSprite::AnimatedSprite() : Sprite() {
            currentFrame = 0;
            resetFinished();
            setRepeat(true);
        }

        AnimatedSprite::AnimatedSprite(const sf::Texture& texture_) : Sprite(texture_) {
            currentFrame = 0;
            resetFinished();
            setRepeat(true);
        }

        AnimatedSprite::AnimatedSprite(const AnimatedSprite& animatedSprite_) : Sprite(animatedSprite_) {
            isEmptyFramesWarningPrinted = animatedSprite_.isEmptyFramesWarningPrinted;
            currentFrame = animatedSprite_.currentFrame;
            frames = animatedSprite_.frames;
            resetFinished();
            setRepeat(true);
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
            if(windowHandle_) {
                windowHandle_->draw(sprite);

            } else {
                const_cast<AnimatedSprite*>(this)->isNullWindowWarningPrinted = true;
                Log::get().write(Log::System::Engine, "[AnimatedSprite] Attempt to draw on 'null' window!");
            }
        }

        void AnimatedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const {
            if(frames.size() > 0) {
                if(isTextureBinded) {
                    target.draw(sprite, states);

                } else if(isTextureBindedWarningPrinted == false) {
                    const_cast<AnimatedSprite*>(this)->isTextureBindedWarningPrinted = true;
                    Log::get().write(Log::System::Engine, "[AnimatedSprite] Attempt to draw without binded texture");
                }

            } else if(isEmptyFramesWarningPrinted == false) {
                const_cast<AnimatedSprite*>(this)->isEmptyFramesWarningPrinted = true;
                Log::get().write(Log::System::Engine, "[AnimatedSprite] Attempt to draw sprite without frames!");
            }
        }

        void AnimatedSprite::insertFrame(const Sprite::Frame& frame_) {
            frames.push_back(frame_);
        }

        void AnimatedSprite::resetCurrentFrame() {
            currentFrame = 0;
        }

        void AnimatedSprite::resetFinished() {
            finished = false;
        }
                
        void AnimatedSprite::setRepeat(bool flag) {
            repeat = flag;
        }

        bool AnimatedSprite::isFinished() const {
            return finished;
        }

        Sprite::Frame& AnimatedSprite::getCurrentFrame() {
            if(currentFrame >= frames.size())
                Log::get().write(
                    Log::System::Engine, 
                    "[AnimatedSprite] Requested acces to %d frame, only %d frames inserted!", 
                    currentFrame - 1, 
                    frames.size()
                );
            
            return frames[currentFrame];
        }

        void AnimatedSprite::setNextFrame() {
            ++currentFrame;

            if(currentFrame == frames.size()) {
                finished = true;

                if(repeat) {
                    resetCurrentFrame();
                } else {
                    --currentFrame;
                }
            }
        }

    }

}