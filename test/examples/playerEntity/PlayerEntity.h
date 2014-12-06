#ifndef PLAYER_ENTITY_H_INCLUDED
#define PLAYER_ENTITY_H_INCLUDED

#include <EngineSystem/Entity/BaseEntity.h>
#include <EngineSystem/Entity/StateMachine.h>

#include "Animation.h"


using namespace Entity;

class PlayerEntity : public BaseEntity {
    private:
    public:
        PlayerEntity(int id);
        ~PlayerEntity();
        void update();
        bool handleMessage(const Message& msg);
        
        
        StateMachine<PlayerEntity>* movementSM;
        Animation animation;

};

#endif // TEST_ENTITY_PLAYER_ENTITY_H_INCLUDED
