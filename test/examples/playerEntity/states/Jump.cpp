#include "Jump.h"

#include "Fall.h"


Jump::Jump() {
    move = false;
}

void Jump::onEnter(PlayerEntity *entity) {
    entity->animation.setCurrentSequence("jump");
}

void Jump::onUpdate(PlayerEntity *entity) {
    entity->animation.update(sf::seconds(Core::frameContext.deltaTime));
    if(entity->animation.getSequence("jump")->isFinished()) {
        entity->movementSM->changeState(new Fall());
        entity->animation.getSequence("jump")->resetFinished();
        return;
    }
    entity->position += sf::Vector2f(0, -3);
    if(move){
        if(entity->flipped){
            entity->position -= sf::Vector2f(3, 0);
        } else {
            entity->position += sf::Vector2f(3, 0);
        }
    }
    move = false;
}

void Jump::onExit(PlayerEntity *entity) {
    (void) entity;
}

bool Jump::onMessage(PlayerEntity* entity, const Message &msg) {
    (void) entity;
    (void) msg;
    
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
    
    
    
    return false;
}