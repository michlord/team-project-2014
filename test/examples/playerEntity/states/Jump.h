#ifndef PLAYERENTITY_STATES_JUMP_H_INCLUDED
#define PLAYERENTITY_STATES_JUMP_H_INCLUDED

#include "../PlayerEntity.h"
#include <EngineSystem/Entity/State.h>
#include <EngineApp/FrameContext.h>

class Jump : public State<PlayerEntity> {
    private:
        bool move;
    public:
        Jump();
        void onEnter(PlayerEntity *entity);
        void onUpdate(PlayerEntity *entity);
        void onExit(PlayerEntity *entity);
        bool onMessage(PlayerEntity* entity, const Message &msg);
};

#endif // PLAYERENTITY_STATES_JUMP_H_INCLUDED
