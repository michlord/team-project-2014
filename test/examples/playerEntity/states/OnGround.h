#ifndef PLAYERENTITY_STATES_ONGROUND_H_INCLUDED
#define PLAYERENTITY_STATES_ONGROUND_H_INCLUDED


#include "../PlayerEntity.h"
#include <EngineSystem/Entity/State.h>


class OnGround : public State<PlayerEntity> {
    private:
    public:
        enum Msg {
            NotTouchingGround
        };
    
        void onEnter(PlayerEntity *entity) {(void) entity;}
        void onUpdate(PlayerEntity *entity) {(void) entity;}
        void onExit(PlayerEntity *entity) {(void) entity;}
        bool onMessage(PlayerEntity* entity, const Message &msg) {
            (void) msg;
            if(msg.msg == Msg::NotTouchingGround) {
                entity->globalSM->changeState(new InAir());
                entity->movementSM->changeState(new Fall());
            }
            return true;
        }
};

#endif // PLAYERENTITY_STATES_ONGROUND_H_INCLUDED
