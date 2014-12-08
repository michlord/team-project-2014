#include "Idle.h"

#include "Run.h"
#include "InAir.h"
#include "Jump.h"

#include "Slash.h"
#include "Cast.h"

void Idle::onEnter(PlayerEntity *entity) {
    entity->canDoubleJump = true;
    entity->animation.setCurrentSequence("idle");
}

void Idle::onUpdate(PlayerEntity *entity) {
    entity->animation.update(sf::seconds(Core::frameContext.deltaTime));
}

void Idle::onExit(PlayerEntity *entity) {
    (void) entity;
}

bool Idle::onMessage(PlayerEntity* entity, const Message &msg) {
    (void) entity;
    if(msg.msg == PlayerEntity::InputMessage::RightPressed) {
        entity->movementSM->changeState(new Run());
        return true;
    }
    if(msg.msg == PlayerEntity::InputMessage::LeftPressed) {
        entity->movementSM->changeState(new Run());
        return true;
    }
    
    if(msg.msg == PlayerEntity::InputMessage::Jump) {
        entity->globalSM->changeState(new InAir());
        entity->movementSM->changeState(new Jump());
        return true;
    }
    
    if(msg.msg == PlayerEntity::InputMessage::Slash) {
        entity->movementSM->changeState(new Slash());
    }
    if(msg.msg == PlayerEntity::InputMessage::Cast) {
        entity->movementSM->changeState(new Cast());
    }
    
    return false;
}