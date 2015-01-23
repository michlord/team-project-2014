#include <Game/Entity/CharacterEntity/States.h>
#include <EngineSystem/Input/Input.h>

namespace Entity {

void Idle::onEnter(CharacterEntity *entity){
    entity->animation.setCurrentSequence("idle");
}

void Idle::onUpdate(CharacterEntity *entity){
    entity->animation.update(sf::seconds(Core::frameContext.deltaTime));
}

void Idle::onExit(CharacterEntity *entity){
    (void) entity;
}

bool Idle::onMessage(CharacterEntity *entity, const Message &msg){
    if(msg.msg == CharacterEntity::MessageType::Input) {
        Input::ID id = (Input::ID) msg.arg1;
        bool pressed = msg.arg2;

        if(pressed) {
            switch(id) {
                case Input::ID::Left : {
                    entity->flipped = true;
                    entity->movementSM->changeState(new Run());
                    return true;
                }
                case Input::ID::Right : {
                    entity->flipped = false;
                    entity->movementSM->changeState(new Run());
                    return true;
                }
                default : break;
            }
        }
    }

    return false;
}

}
