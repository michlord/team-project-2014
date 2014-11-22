#ifndef TEST_ENTITY_PLAYER_ENTITY_H_INCLUDED
#define TEST_ENTITY_PLAYER_ENTITY_H_INCLUDED

#include <EngineSystem/Entity/BaseEntity.h>
#include <EngineSystem/Entity/StateMachine.h>

#include "Animation.h"


using namespace Entity;

class PlayerEntity : public BaseEntity {
    private:
        StateMachine<PlayerEntity>* movementSM;
        
        
        PlayerEntity(const PlayerEntity& other);
        PlayerEntity &operator=(const PlayerEntity& other);
    public:
        PlayerEntity(int id);
        ~PlayerEntity();
        void update();
        bool handleMessage(const Message& msg);
        StateMachine<PlayerEntity>* getMovementSM();
        
        Animation animation;

};

#endif // TEST_ENTITY_PLAYER_ENTITY_H_INCLUDED
