#include "PlayerStates.h"


bool IdleState::onMessage(PlayerEntity* entity, const Message &msg) {
    UNUSED(entity)
    //UNUSED(msg)
    
    if(msg.msg == PLAYER_MESSAGES::Jump) {
        State<PlayerEntity> *old = entity->getMovementSM()->changeState(new JumpState());
        delete old;
        return true;
    }
    
    return false;
}