#include <Game/Level/Tile.h>
#include <Game/Scene/Gameplay.h>
#include <EngineApp/FrameContext.h>

namespace Level {

    Tile::Tile() {
        setType(Tile::Type::Empty);
    }

    Tile::Tile(Tile::Type type_) {
        setType(type_);
    }

    Tile::~Tile() {

    }

    void Tile::update(const sf::Time& timeElapsed) {
        if(sprite)
            sprite->update(timeElapsed);
    }

    void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        if(sprite && type != Tile::Type::Empty) {
            //states.transform.translate(-Scene::Gameplay::cameraCenter);
            target.draw(*sprite, states);
        }
    }

    void Tile::setPosition(const sf::Vector2f& position) {
        if(sprite)
            sprite->setPosition(position);
    }

    void Tile::setType(Type type_) {
        type = type_;

        const sf::Texture& text = Core::frameContext.assetsManager->getTexture("tiles_atlas");
        Video::Render::Sprite::Frame frame;
        sf::Vector2f position;

        if(sprite) {
            position = sprite->getPosition();
            sprite.reset();
        }

        sprite.reset(new Video::Render::Sprite());
        sprite->setPosition(position * 32.0f);

        switch(type) {
            case Type::Empty:
                // do not draw this (draw method check if type != Empty)
                frame.setTextureSegment(sf::IntRect(0, 0, 128, 128));
                break;

            case Type::Brick:
                frame.setTextureSegment(sf::IntRect(128, 0, 128, 128));
                break;
        }

        sprite->insertFrame(frame);
        sprite->bindTexture(text);
        sprite->setSize(32, 32);
        sprite->update(sf::Time(sf::seconds(0.0f)));
    }

    Tile::Type Tile::getType() const {
        return type;
    }

    const sf::Vector2f& Tile::getPosition() const {
        return sprite->getPosition();
    }

}
