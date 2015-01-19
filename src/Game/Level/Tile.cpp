#include <Game/Level/Tile.h>
#include <EngineApp/FrameContext.h>

namespace Level {

    Tile::Tile() {
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
            sprite.reset();
        }

        // There should probably be only one texture atlas for tiles.
        // In the following switch statement the
        // sprite should be assigned an appropriate texture rect.

        // BTW As a code refactor the global instance of assetsManager might
        // soon be moved out of the frameContext...
        static const sf::Texture &text = Core::frameContext.assetsManager->getTexture("tiles_atlas");

        switch(type) {
            case Type::Empty:
                sprite.reset(new Video::Render::Sprite());
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
