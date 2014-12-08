#include "Fall.h"

#include "OnGround.h"
#include "Idle.h"
#include "Jump.h"

Fall::Fall(){
    move = false;
}

void Fall::onEnter(PlayerEntity *entity) {
    entity->animation.setCurrentSequence("fall");
}

void Fall::onUpdate(PlayerEntity *entity) {
    entity->animation.update(sf::seconds(Core::frameContext.deltaTime));
    entity->position += sf::Vector2f(0, 3);
    if(move){
        if(entity->flipped){
            entity->position -= sf::Vector2f(3, 0);
        } else {
            entity->position += sf::Vector2f(3, 0);
        }
    }
    move = false;
}

void Fall::onExit(PlayerEntity *entity) {
    (void) entity;
}

bool Fall::onMessage(PlayerEntity* entity, const Message &msg) {
    (void) entity;
    if(msg.msg == Msg::TouchingGround) {
        entity->globalSM->changeState(new OnGround());
        entity->movementSM->changeState(new Idle());
    }
    if(msg.msg == PlayerEntity::InputMessage::RightPressed) {
        move = true;
        return true;
    }
    if(msg.msg == PlayerEntity::InputMessage::LeftPressed) {
        move = true;
        return true;
    }
    
    if(entity->canDoubleJump && msg.msg == PlayerEntity::InputMessage::Jump) {
        entity->canDoubleJump = false;
        entity->movementSM->changeState(new Jump());
        return true;
    }
    
    return true;
}