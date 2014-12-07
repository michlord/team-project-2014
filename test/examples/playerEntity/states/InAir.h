#ifndef PLAYERENTITY_STATES_INAIR_H_INCLUDED
#define PLAYERENTITY_STATES_INAIR_H_INCLUDED

#include "../PlayerEntity.h"
#include <EngineSystem/Entity/State.h>

class InAir : public State<PlayerEntity> {
    private:
    public:    
        void onEnter(PlayerEntity *entity) {(void) entity;}
        void onUpdate(PlayerEntity *entity) {(void) entity;}
        void onExit(PlayerEntity *entity) {(void) entity;}
        bool onMessage(PlayerEntity* entity, const Message &msg) {
            (void) entity;
            (void) msg;
            return true;
        }
};

#endif // PLAYERENTITY_STATES_INAIR_H_INCLUDED
