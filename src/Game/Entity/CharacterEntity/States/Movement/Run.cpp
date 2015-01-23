#include <Game/Entity/CharacterEntity/States.h>

namespace Entity {

    void Run::onEnter(CharacterEntity *entity){
        entity->animation.setCurrentSequence("run");
    }

    void Run::onUpdate(CharacterEntity *entity){
        entity->animation.update(sf::seconds(Core::frameContext.deltaTime));
        if(entity->flipped){
            entity->setFeetPosition(entity->getFeetPosition() - sf::Vector2f(3, 0));
        } else {
            entity->setFeetPosition(entity->getFeetPosition() + sf::Vector2f(3, 0));
        }
        
    }

    void Run::onExit(CharacterEntity *entity){
        (void) entity;
    }

    bool Run::onMessage(CharacterEntity *entity, const Message &msg){
        if(msg.msg == CharacterEntity::MessageType::Input) {
            Input::ID id = (Input::ID) msg.arg1;
            int pressed = msg.arg2;

            if(!pressed) {
                if(entity->flipped && id == Input::ID::Left) {
                    entity->movementSM->changeState(new Idle());
                    return true;
                }
                if(!entity->flipped && id == Input::ID::Right) {
                    entity->movementSM->changeState(new Idle());
                    return true;
                }
            }
        }

        return false;
    }

}
