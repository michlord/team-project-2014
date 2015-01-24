#include <Game/Entity/CharacterEntity/States.h>

namespace Entity {

    void OnGround::onEnter(CharacterEntity *entity){
        (void) entity;
    }

    void OnGround::onUpdate(CharacterEntity *entity){
        (void) entity;
        if(entity->getFeetPosition().y < 200) {
            entity->movementSM->changeState(new Fall());
            entity->globalMovementSM->changeState(new InAir());
        }
    }

    void OnGround::onExit(CharacterEntity *entity){
        (void) entity;
    }

    bool OnGround::onMessage(CharacterEntity *entity, const Message &msg){
        if(msg.msg == CharacterEntity::MessageType::Input) {
            Input::ID id = (Input::ID) msg.arg1;
            int pressed = msg.arg2;

            if(pressed) {
                switch(id) {
                    case Input::ID::Space : {
                        entity->globalMovementSM->changeState(new InAir());
                        entity->movementSM->changeState(new Jump());
                        return true;
                    }
                    default : break;
                }
            }
        }

        return false;
    }

}
