#include "InAir.h"



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
    return true;
}