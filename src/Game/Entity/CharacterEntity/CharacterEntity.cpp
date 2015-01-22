#include <Game/Entity/CharacterEntity/CharacterEntity.h>

namespace Entity {

CharacterEntity::CharacterEntity(int id)
 : BaseEntity(id)
{

}

CharacterEntity::~CharacterEntity() {

}

void CharacterEntity::update() {

}

bool CharacterEntity::handleMessage(const Message& msg) {
    (void) msg;
    return true;
}

void CharacterEntity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    (void) target; (void) states;
}


}
