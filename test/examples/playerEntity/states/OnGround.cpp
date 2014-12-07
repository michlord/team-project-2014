#include "OnGround.h"

#include "InAir.h"
#include "Fall.h"
#include "Idle.h"
#include "Run.h"

void OnGround::onEnter(PlayerEntity *entity) {
    (void) entity; 
    onGround = true;
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
    
    
    
    
    
    return true;
}