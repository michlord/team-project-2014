#include "OnGround.h"

#include "InAir.h"
#include "Fall.h"
#include "Idle.h"
#include "Run.h"

void OnGround::onEnter(PlayerEntity *entity) {
    (void) entity; 
    onGround = true;
    entity->slashedInAir = false;
}

void OnGround::onUpdate(PlayerEntity *entity) {
    (void) entity;
    if(!onGround) {
        entity->globalSM->changeState(new InAir());
        entity->movementSM->changeState(new Fall());
    }
    
    onGround = false;
}
void OnGround::onExit(PlayerEntity *entity) {
    (void) entity;
}

bool OnGround::onMessage(PlayerEntity* entity, const Message &msg) {
    (void) entity;
    (void) msg;
    if(msg.msg == Msg::TouchingGround) {
        onGround = true;
    }
    
    if(msg.msg == PlayerEntity::InputMessage::RightPressed) {
        entity->flipped = false;
        return true;
    }
    if(msg.msg == PlayerEntity::InputMessage::LeftPressed) {
        entity->flipped = true;
        return true;
    }
    
    
    
    return true;
}