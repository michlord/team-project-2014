#include "EngineSystem/Video/Render/Sprite.h"

namespace Video {

    namespace Render {

        Sprite::Sprite() {
            texturePtr = nullptr;
        }

        Sprite::Sprite(sf::Texture& texture_) {
            bindTexture(texture_);
        }

        Sprite::Sprite(sf::Texture& texture_, const sf::IntRect& textureSegment_) {
            bindTexture(texture_);
            setTextureSegment(textureSegment_);
        }

        void Sprite::draw(sf::RenderWindow* windowHandle_) {
            windowHandle_->draw(sprite);
        }

        void Sprite::bindTexture(sf::Texture& texture_) {
            texturePtr = &texture_;
            sprite.setTexture(*texturePtr, true);
        }

        void Sprite::setRotation(float angle_) {
            rotation = angle_;
            sprite.setRotation(rotation);
        }

        void Sprite::setSize(const sf::Vector2u& size_) {                   // to be fixed!
            sf::Vector2i segmentSize;
            sf::Vector2f newScale;

            size = size_;
            segmentSize = sf::Vector2i(sprite.getTextureRect().width, sprite.getTextureRect().height);

            newScale.x = static_cast<float>(size.x) / static_cast<float>(segmentSize.x);
            newScale.y = static_cast<float>(size.y) / static_cast<float>(segmentSize.y);

            sprite.setScale(newScale);
        }

        void Sprite::setPosition(const sf::Vector2f& position_) {
            position = position_;
            sprite.setPosition(position);
        }

        void Sprite::setTextureSegment(const sf::IntRect& segment_) {
            textureSegment = segment_;
            sprite.setTextureRect(textureSegment);
        }

        void Sprite::setColorMask(const sf::Color& mask_) {
            colorMask = mask_;
            sprite.setColor(colorMask);
        }

        void Sprite::movePosition(const sf::Vector2f& moveVector_) {
            position += moveVector_;
            sprite.move(moveVector_);
        }

        void Sprite::setSize(unsigned int width_, unsigned int height_) {
            setSize(sf::Vector2u(width_, height_));
        }

        void Sprite::setPosition(float positionX_, float positionY_) {
            setPosition(sf::Vector2f(positionX_, positionY_));
        }

        void Sprite::setTextureSegment(int left_, int top_, int width_, int height_) {
            setTextureSegment(sf::IntRect(left_, top_, width_, height_));
        }

        void Sprite::movePosition(float offsetX_, float offsetY_) {
            movePosition(sf::Vector2f(offsetX_, offsetY_));
        }
                
        float Sprite::getRotation() const {
            return rotation;
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

        const sf::IntRect& Sprite::getTextureSegment() const {
            return textureSegment;
        }

        const sf::Color& Sprite::getColorMask() const {
            return colorMask;
        }

    }

}