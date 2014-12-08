#include "AirSlash.h"
#include "Fall.h"


void AirSlash::onEnter(PlayerEntity *entity) {
    (void) entity;
    entity->animation.setCurrentSequence("slash");
}

void AirSlash::onUpdate(PlayerEntity *entity) {
    (void) entity;
    entity->animation.update(sf::seconds(Core::frameContext.deltaTime));
    if(entity->animation.getSequence("slash")->isFinished()) {
        entity->movementSM->changeState(new Fall());
        entity->animation.getSequence("slash")->resetFinished();
        return;
    }
    
}

void AirSlash::onExit(PlayerEntity *entity) {
    (void) entity;
}

bool AirSlash::onMessage(PlayerEntity* entity, const Message &msg) {
    (void) entity;
    (void) msg;    
    return true;
}