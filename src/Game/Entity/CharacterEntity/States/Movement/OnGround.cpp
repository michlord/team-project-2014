#include <Game/Entity/CharacterEntity/States.h>

namespace Entity {

    void OnGround::onEnter(CharacterEntity *entity){
        (void) entity;
    }

    void OnGround::onUpdate(CharacterEntity *entity){
        (void) entity;
        if(entity->getFeetPosition().y < 120) {
            entity->movementSM->changeState(new Fall());
            entity->globalMovementSM->changeState(new InAir());
        }
    }

    void OnGround::onExit(CharacterEntity *entity){
        (void) entity;
    }

    bool OnGround::onMessage(CharacterEntity *entity, const Message &msg){
        (void) entity; (void) msg;
        return true;
    }

}
