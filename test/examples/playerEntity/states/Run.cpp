#include "Run.h"

#include "Idle.h"


void Run::onEnter(PlayerEntity *entity) {
    entity->animation.setCurrentSequence("run");
}

void Run::onUpdate(PlayerEntity *entity) {
    entity->animation.update(sf::seconds(Core::frameContext.deltaTime));
    entity->position += sf::Vector2f(3, 0);
}

void Run::onExit(PlayerEntity *entity) {
    (void) entity;
}

bool Run::onMessage(PlayerEntity* entity, const Message &msg) {
    if(msg.msg == PlayerEntity::InputMessage::RightDepressed) {
        entity->movementSM->changeState(new Idle());
        return true;
    }
    return false;
}