#include "PlayerStates.h"
#include <memory>


bool IdleState::onMessage(PlayerEntity* entity, const Message &msg) {
    UNUSED(entity)
    //UNUSED(msg)
    
    if(msg.msg == PLAYER_MESSAGES::Jump) {
        //State<PlayerEntity>::StatePtr old = 
        entity->getMovementSM()->changeState(new JumpState());
        return true;
    }
    
    return false;
}