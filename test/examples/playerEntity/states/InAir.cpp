#include "InAir.h"

#include "AirSlash.h"


void InAir::onEnter(PlayerEntity *entity) {
    (void) entity;
}

void InAir::onUpdate(PlayerEntity *entity) {
    (void) entity;
    
}

void InAir::onExit(PlayerEntity *entity) {
    (void) entity;
}

bool InAir::onMessage(PlayerEntity* entity, const Message &msg) {
    (void) entity;
    (void) msg;
    
    if(msg.msg == PlayerEntity::InputMessage::RightPressed) {
        entity->flipped = false;
        return true;
    }
    if(msg.msg == PlayerEntity::InputMessage::LeftPressed) {
        entity->flipped = true;
        return true;
    }
    
    if(!entity->slashedInAir && msg.msg == PlayerEntity::InputMessage::Slash) {
        entity->slashedInAir = true;
        entity->movementSM->changeState(new AirSlash());
    }
    
    return true;
}