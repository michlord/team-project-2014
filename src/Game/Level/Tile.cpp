#include <Game/Level/Tile.h>

namespace Level {

    Tile::Tile() {
        sprite = nullptr;
    }

    Tile::Tile(Tile::Type type_) {
        setType(type_);
    }

    Tile::~Tile() {
        if(sprite != nullptr) {
            delete sprite;
            sprite = nullptr;
        }
    }

    void Tile::update(const sf::Time& timeElapsed) {
        if(sprite)
            sprite->update(timeElapsed);
    }

    void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        if(sprite)
            sprite->draw(target, states);
    }
 
    void Tile::setPosition(const sf::Vector2f& position) {
        if(sprite)
            sprite->setPosition(position);
    }

    void Tile::setType(Type type) {
        sf::Vector2f position;

        if(sprite) {
            position = sprite->getPosition();
            delete sprite;
        }

        
        static const sf::Texture text;
        //TODO:
        //static const sf::Texture& = assetManager.getTexture("id");

        switch(type) {
            case Type::Empty: 
                sprite = new Video::Render::Sprite();
                sprite->bindTexture(text);
                sprite->setPosition(position);
                break;

            // case Type::other:
        }
    }

    Tile::Type Tile::getType() const {
        return type;
    }

    const sf::Vector2f& Tile::getPosition() const {
        return sprite->getPosition();
    }

}