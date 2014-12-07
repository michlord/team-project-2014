#include "Run.h"

#include "Idle.h"

Run::Run(Direction direction_)
 : direction(direction_)
{

}

void Run::onEnter(PlayerEntity *entity) {
    entity->animation.setCurrentSequence("run");
    if(direction == Direction::Left) {
        //entity->animation.flipHorizontal();
    }
}

void Run::onUpdate(PlayerEntity *entity) {
    entity->animation.update(sf::seconds(Core::frameContext.deltaTime));
    if(direction == Direction::Right) {
        entity->position += sf::Vector2f(3, 0);
    } else {
        entity->position -= sf::Vector2f(3, 0);
    }
}

void Run::onExit(PlayerEntity *entity) {
    (void) entity;
    if(direction == Direction::Left) {
        //entity->animation.unflipHorizontal();
    }
}

bool Run::onMessage(PlayerEntity* entity, const Message &msg) {
    if(direction == Direction::Right) {
        if(msg.msg == PlayerEntity::InputMessage::RightDepressed) {
            entity->movementSM->changeState(new Idle());
            return true;
        }
    } else {
        if(msg.msg == PlayerEntity::InputMessage::LeftDepressed) {
            entity->movementSM->changeState(new Idle());
            return true;
        }
    }
    return false;
}