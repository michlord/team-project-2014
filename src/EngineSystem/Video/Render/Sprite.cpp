#include "EngineSystem/Video/Render/Sprite.h"
#include "EngineSystem/Log/Log.h"

namespace Video {

    namespace Render {

        /**
         * Sprite class implementation
         */

        Sprite::Sprite() {
            frameCount = 0;
            isTextureBinded = false;
            isTextureBindedWarningPrinted = false;
            isTextureBindedWarningPrinted = false;
        }

        Sprite::Sprite(const sf::Texture& texture_) {
            frameCount = 0;
            isTextureBinded = false;
            isTextureBindedWarningPrinted = false;
            isTextureBindedWarningPrinted = false;

            bindTexture(texture_);
        }

        Sprite::Sprite(const sf::Texture& texture_, const Sprite::Frame& frame_) {
            frameCount = 0;
            isTextureBinded = false;
            isTextureBindedWarningPrinted = false;
            isTextureBindedWarningPrinted = false;

            bindTexture(texture_);
            insertFrame(frame_);
        }

        Sprite::Sprite(const Sprite& sprite_) {
            isTextureBinded = sprite_.isTextureBinded;
            isTextureBindedWarningPrinted = sprite_.isTextureBindedWarningPrinted;
            isNullWindowWarningPrinted = sprite_.isNullWindowWarningPrinted;

            frameCount = sprite_.frameCount;
            rotation = sprite_.rotation;
            colorMask = sprite_.colorMask;
            size = sprite_.size;
            position = sprite_.position;

            sprite = sprite_.sprite;
            frame = sprite_.frame;
        }

        Sprite::~Sprite() {

        }

        void Sprite::update(const sf::Time& timeElapsed_) {
            frame.update(timeElapsed_);

            sprite.setTextureRect(frame.getTextureSegment());
            setSize(size);
        }

        void Sprite::draw(sf::RenderWindow* windowHandle_) const {
            if(windowHandle_) {
                draw(*windowHandle_);

            } else if(isNullWindowWarningPrinted == false) {
                const_cast<Sprite*>(this)->isNullWindowWarningPrinted = true;
                Log::get().write(Log::System::Engine, "[Sprite] Attempt to draw on 'null' window");
            }
        }

        void Sprite::draw(sf::RenderTarget &target, sf::RenderStates states) const {
            if(isTextureBinded) {
                target.draw(sprite, states);

            } else if(isTextureBindedWarningPrinted == false) {
                const_cast<Sprite*>(this)->isTextureBindedWarningPrinted = true;
                Log::get().write(Log::System::Engine, "[Sprite] Attempt to draw without binded texture");
            }
        }

        void Sprite::bindTexture(const sf::Texture& texture_) {
            isTextureBinded = true;
            sprite.setTexture(texture_, true);
        }

        void Sprite::insertFrame(const Sprite::Frame& frame_) {
            frameCount = 1;
            frame = frame_;
        }

        void Sprite::resetCurrentFrame() {

        }

        void Sprite::setRotation(float angle_) {
            rotation = angle_;
            sprite.setRotation(rotation);
        }

        void Sprite::setSize(const sf::Vector2u& size_) {                   // to be fixed!
            sf::Vector2i segmentSize;

            size = size_;
            segmentSize = sf::Vector2i(sprite.getTextureRect().width, sprite.getTextureRect().height);

            newScale.x = static_cast<float>(size.x) / static_cast<float>(segmentSize.x);
            newScale.y = static_cast<float>(size.y) / static_cast<float>(segmentSize.y);

            sprite.setScale(newScale);
        }

        void Sprite::setSize(unsigned int width_, unsigned int height_) {
            setSize(sf::Vector2u(width_, height_));
        }

        void Sprite::setPosition(const sf::Vector2f& position_) {
            position = position_;
            sprite.setPosition(position);
        }

        void Sprite::setPosition(float positionX_, float positionY_) {
            setPosition(sf::Vector2f(positionX_, positionY_));
        }

        void Sprite::setColorMask(const sf::Color& mask_) {
            colorMask = mask_;
            sprite.setColor(colorMask);
        }

        void Sprite::movePosition(const sf::Vector2f& moveVector_) {
            position += moveVector_;
            sprite.move(moveVector_);
        }

        void Sprite::movePosition(float offsetX_, float offsetY_) {
            movePosition(sf::Vector2f(offsetX_, offsetY_));
        }

        float Sprite::getRotation() const {
            return rotation;
        }

        unsigned int Sprite::getFrameCount() const {
            return frameCount;
        }

        unsigned int Sprite::getWidth() const {
            return size.x;
        }

        unsigned int Sprite::getHeight() const {
            return size.y;
        }

        const sf::Vector2u& Sprite::getSize() const {
            return size;
        }

        const sf::Vector2f& Sprite::getPosition() const {
            return position;
        }

        const sf::Color& Sprite::getColorMask() const {
            return colorMask;
        }

        const Sprite::Frame* Sprite::getFrames() const {
            return &frame;
        }

        sf::Vector2f Sprite::getNewScale() const {
            return newScale;
        }

        /**
         * Sprite::Frame class implementation
         */
        Sprite::Frame::Frame() {
            setDuration(sf::seconds(1.0f));     // default frame duration = 1s
        }

        Sprite::Frame::Frame(const sf::IntRect& textureSegment_, const sf::Time& duration_) {
            setDuration(duration_);
            setTextureSegment(textureSegment_);
        }

        Sprite::Frame::Frame(const Sprite::Frame& frame_) {
            timeLeft = frame_.timeLeft;
            duration = frame_.duration;
            textureSegment = frame_.textureSegment;
        }

        void Sprite::Frame::reset() {
            setTimeLeft(duration);
        }

        const sf::Time& Sprite::Frame::update(const sf::Time& timeElapsed_) {
            setTimeLeft(getTimeLeft() - timeElapsed_);
            return getTimeLeft();
        }

        void Sprite::Frame::setDuration(const sf::Time& time) {
            duration = time;
            reset();
        }

        void Sprite::Frame::setTextureSegment(const sf::IntRect& textureSegment_) {
            textureSegment = textureSegment_;
        }

        const sf::Time& Sprite::Frame::getTimeLeft() const {
            return timeLeft;
        }

        const sf::Time& Sprite::Frame::getDuration() const {
            return duration;
        }

        const sf::IntRect& Sprite::Frame::getTextureSegment() const {
            return textureSegment;
        }

        void Sprite::Frame::setTimeLeft(const sf::Time& time_) {
            timeLeft = time_;
        }
    }

}
