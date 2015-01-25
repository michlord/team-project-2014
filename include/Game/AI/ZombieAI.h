#ifndef GAME_AI_ZOMBIEAI_H_INCLUDED
#define GAME_AI_ZOMBIEAI_H_INCLUDED

#include <EngineSystem/Entity/BaseEntity.h>
#include <EngineSystem/Entity/StateMachine.h>
#include <EngineSystem/Input/Input.h>

#include <Game/Level/Level.h>
#include <Game/Entity/CharacterEntity/CharacterEntity.h>


namespace AI {

    class ZombieAI : public Entity::BaseEntity {
    private:
        ZombieAI(const ZombieAI &other_);
        ZombieAI &operator=(const ZombieAI &other_);
    public:
        ZombieAI(int id, Entity::CharacterEntity *character_ = nullptr);
        ~ZombieAI();

        void update();
        bool handleMessage(const Entity::Message& msg);

        std::unique_ptr< Entity::StateMachine<ZombieAI> > SM;
        Entity::CharacterEntity *character;
        Entity::CharacterEntity *player;
    };

}

#endif // GAME_AI_ZOMBIEAI_H_INCLUDED
