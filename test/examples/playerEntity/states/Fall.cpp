#include "Fall.h"

#include "OnGround.h"
#include "Idle.h"


void Fall::onEnter(PlayerEntity *entity) {
    entity->animation.setCurrentSequence("fall");
}

void Fall::onUpdate(PlayerEntity *entity) {
    entity->animation.update(sf::seconds(Core::frameContext.deltaTime));
    entity->position += sf::Vector2f(0, 3);
}

void Fall::onExit(PlayerEntity *entity) {
    (void) entity;
}

bool Fall::onMessage(PlayerEntity* entity, const Message &msg) {
    (void) entity;
    if(msg.msg == Msg::TouchingGround) {
        entity->globalSM->changeState(new OnGround());
        entity->movementSM->changeState(new Idle());
    }
    return true;
}