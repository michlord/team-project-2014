#include "Slash.h"
#include "Idle.h"

void Slash::onEnter(PlayerEntity *entity) {
    (void) entity;
    entity->animation.setCurrentSequence("slash");
}

void Slash::onUpdate(PlayerEntity *entity) {
    (void) entity;
    entity->animation.update(sf::seconds(Core::frameContext.deltaTime));
    if(entity->animation.getSequence("slash")->isFinished()) {
        entity->movementSM->changeState(new Idle());
        entity->animation.getSequence("slash")->resetFinished();
        return;
    }
    
}

void Slash::onExit(PlayerEntity *entity) {
    (void) entity;
}

bool Slash::onMessage(PlayerEntity* entity, const Message &msg) {
    (void) entity;
    (void) msg;    
    return true;
}