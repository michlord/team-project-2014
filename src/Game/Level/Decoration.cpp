#include <Game/Level/Decoration.h>

namespace Level {

    Decoration::Decoration() {

    }

    Decoration::Decoration(int posX_, int posY_, int level_, const std::string& id_) {
        posX = posX_;
        posY = posY_;
        level = level_;
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

    int Decoration::getLevel() const {
        return level;
    }

}