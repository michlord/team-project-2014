#include "Jump.h"

#include "Fall.h"


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
}

void Jump::onExit(PlayerEntity *entity) {
    (void) entity;
}

bool Jump::onMessage(PlayerEntity* entity, const Message &msg) {
    (void) entity;
    (void) msg;
    return false;
}