#include <Game/Entity/CharacterEntity/States.h>

namespace Entity {

    void Fall::onEnter(CharacterEntity *entity){
        (void) entity;
        entity->animation.setCurrentSequence("fall");
    }

    void Fall::onUpdate(CharacterEntity *entity){
        (void) entity;
        entity->animation.update(sf::seconds(Core::frameContext.deltaTime));
        entity->setFeetPosition(entity->getFeetPosition() + sf::Vector2f(0.0f, 2.0f));
    }

    void Fall::onExit(CharacterEntity *entity){
        (void) entity;
    }

    bool Fall::onMessage(CharacterEntity *entity, const Message &msg){
        (void) entity; (void) msg;
        return true;
    }

}
