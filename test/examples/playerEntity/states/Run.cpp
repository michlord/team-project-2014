#include "Run.h"

#include "Idle.h"
#include "InAir.h"
#include "Jump.h"

#include "Slash.h"
#include "Cast.h"

void Run::onEnter(PlayerEntity *entity) {
    entity->animation.setCurrentSequence("run");
}

void Run::onUpdate(PlayerEntity *entity) {
    entity->animation.update(sf::seconds(Core::frameContext.deltaTime));
    if(entity->flipped){
        entity->position -= sf::Vector2f(3, 0);
    } else {
        entity->position += sf::Vector2f(3, 0);
    }
}

void Run::onExit(PlayerEntity *entity) {
    (void) entity;
}

bool Run::onMessage(PlayerEntity* entity, const Message &msg) {
    if(entity->flipped){
        if(msg.msg == PlayerEntity::InputMessage::LeftDepressed) {
            entity->movementSM->changeState(new Idle());
            return true;
        }
    } else {
        if(msg.msg == PlayerEntity::InputMessage::RightDepressed) {
            entity->movementSM->changeState(new Idle());
            return true;
        }
    }
    
    if(msg.msg == PlayerEntity::InputMessage::Jump) {
        entity->globalSM->changeState(new InAir());
        entity->movementSM->changeState(new Jump());
        return true;
    }
    
    if(msg.msg == PlayerEntity::InputMessage::Slash) {
        entity->movementSM->changeState(new Slash());
    }
    if(msg.msg == PlayerEntity::InputMessage::Cast) {
        entity->movementSM->changeState(new Cast());
    }
    
    return false;
}