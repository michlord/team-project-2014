#include <GameSystem/Level/Decoration.h>

namespace Level {

    Decoration::Decoration() {

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

}