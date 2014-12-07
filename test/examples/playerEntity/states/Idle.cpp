#include "Idle.h"

#include "Run.h"

void Idle::onEnter(PlayerEntity *entity) {
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
        entity->movementSM->changeState(new Run(Run::Direction::Right));
        return true;
    }
    if(msg.msg == PlayerEntity::InputMessage::LeftPressed) {
        entity->movementSM->changeState(new Run(Run::Direction::Left));
        return true;
    }
    
    return false;
}