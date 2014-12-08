#include "Cast.h"
#include "Idle.h"

void Cast::onEnter(PlayerEntity *entity) {
    (void) entity;
    entity->animation.setCurrentSequence("cast");
}

void Cast::onUpdate(PlayerEntity *entity) {
    (void) entity;
    entity->animation.update(sf::seconds(Core::frameContext.deltaTime));
    if(entity->animation.getSequence("cast")->isFinished()) {
        entity->movementSM->changeState(new Idle());
        entity->animation.getSequence("cast")->resetFinished();
        return;
    }
    
}

void Cast::onExit(PlayerEntity *entity) {
    (void) entity;
}

bool Cast::onMessage(PlayerEntity* entity, const Message &msg) {
    (void) entity;
    (void) msg;    
    return true;
}