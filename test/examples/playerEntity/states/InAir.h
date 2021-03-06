#ifndef PLAYERENTITY_STATES_INAIR_H_INCLUDED
#define PLAYERENTITY_STATES_INAIR_H_INCLUDED

#include "../PlayerEntity.h"
#include <EngineSystem/Entity/State.h>
#include <EngineApp/FrameContext.h>

class InAir : public State<PlayerEntity> {
    private:
    public:  
        void onEnter(PlayerEntity *entity);
        void onUpdate(PlayerEntity *entity);
        void onExit(PlayerEntity *entity);
        bool onMessage(PlayerEntity* entity, const Message &msg);
};




#endif // PLAYERENTITY_STATES_INAIR_H_INCLUDED
