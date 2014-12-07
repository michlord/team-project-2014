#ifndef PLAYERENTITY_STATES_FALL_H_INCLUDED
#define PLAYERENTITY_STATES_FALL_H_INCLUDED

#include "../PlayerEntity.h"
#include <EngineSystem/Entity/State.h>
#include <EngineApp/FrameContext.h>

class Fall : public State<PlayerEntity> {
    private:
    public:
        enum Msg {
            TouchedGround
        };
        
        void onEnter(PlayerEntity *entity) {
            entity->animation.setCurrentSequence("fall");
        }
        
        void onUpdate(PlayerEntity *entity) {
            entity->animation.update(sf::seconds(Core::frameContext.deltaTime));
        }
        
        void onExit(PlayerEntity *entity) {
            (void) entity;
        }
        
        bool onMessage(PlayerEntity* entity, const Message &msg) {
            (void) entity;
            (void) msg;
            return true;
        }
};


#endif // PLAYERENTITY_STATES_FALL_H_INCLUDED
