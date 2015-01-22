#include <Game/Level/Decoration.h>

namespace Level {

    Decoration::Decoration() {

    }

    Decoration::Decoration(int posX_, int posY_, int scale_, const std::string& id_) {
        posX = posX_;
        posY = posY_;
        scale = scale_;
        id = id_;
    }

    Decoration::~Decoration() {

    }

    void Decoration::update(const sf::Time& timeElapsed) {
        if(sprite)
            sprite->update(timeElapsed);
    }

    void Decoration::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        if(sprite)
            sprite->draw(target, states);
    }

    int Decoration::getScale() const {
        return scale;
    }

}