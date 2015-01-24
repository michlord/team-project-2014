#include <Game/Entity/CharacterEntity/States.h>

namespace Entity {

    void Slash::onEnter(CharacterEntity *entity){
        entity->animation.setCurrentSequence("slash");

    }

    void Slash::onUpdate(CharacterEntity *entity){
        entity->animation.update(sf::seconds(Core::frameContext.deltaTime));
        if(entity->animation.getSequence("slash")->isFinished()) {
            entity->movementSM->changeState(new Idle());
            entity->animation.getSequence("slash")->resetFinished();
            return;
        }
    }

    void Slash::onExit(CharacterEntity *entity){
        (void) entity;
    }

    bool Slash::onMessage(CharacterEntity *entity, const Message &msg){
        (void) entity; (void) msg;
        return true;
    }

}
