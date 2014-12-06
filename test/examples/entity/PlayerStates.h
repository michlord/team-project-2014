#ifndef TEST_ENTITY_PLAYER_STATES_H_INCLUDED
#define TEST_ENTITY_PLAYER_STATES_H_INCLUDED

#define UNUSED(x) (void)x;

#include "PlayerEntity.h"
#include <EngineSystem/Entity/State.h>

enum PLAYER_MESSAGES {
    Jump
};

extern sf::Time frameTime;

class IdleState : public State<PlayerEntity> {
    virtual void onEnter(PlayerEntity *entity) {
        entity->animation.setAnimation("idle");
    }
    
    virtual void onUpdate(PlayerEntity *entity) {
        entity->animation.update(frameTime.asSeconds());
    }
    
    virtual void onExit(PlayerEntity *entity) {
        UNUSED(entity)
    }
    
    virtual bool onMessage(PlayerEntity* entity, const Message &msg);
};

class JumpState : public State<PlayerEntity> {
    float duration;

    virtual void onEnter(PlayerEntity *entity) {
        duration = 0.3f;
        entity->animation.setAnimation("jump");
    }
    
    virtual void onUpdate(PlayerEntity *entity) {
        duration -= frameTime.asSeconds();
        if(duration <= 0.0f) {
            entity->getMovementSM()->changeState(new IdleState());
        }
        
        entity->animation.update(frameTime.asSeconds());
    }
    
    virtual void onExit(PlayerEntity *entity) {
        UNUSED(entity)
    }
    
    virtual bool onMessage(PlayerEntity* entity, const Message &msg) {
        UNUSED(entity)
        UNUSED(msg)
        return true;
    }
};



#endif // TEST_ENTITY_PLAYER_STATES_H_INCLUDED
