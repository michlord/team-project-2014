#include "PlayerEntity.h"
#include "PlayerStates.h"

using namespace Entity;

PlayerEntity::PlayerEntity(int id)
 : BaseEntity(id)
{
    movementSM = new StateMachine<PlayerEntity>(this);
    movementSM->changeState(new IdleState());
}

PlayerEntity::~PlayerEntity() {
    delete movementSM->getCurrentState();
    delete movementSM;
}

void PlayerEntity::update(){
    movementSM->update();
}

bool PlayerEntity::handleMessage(const Message& msg){
    movementSM->handleMessage(msg);
    return true;
}

StateMachine<PlayerEntity>* PlayerEntity::getMovementSM(){
    return movementSM;
}
