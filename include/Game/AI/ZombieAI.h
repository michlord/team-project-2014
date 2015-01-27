#ifndef GAME_AI_ZOMBIEAI_H_INCLUDED
#define GAME_AI_ZOMBIEAI_H_INCLUDED

#include <Game/AI/BaseAI.h>
#include <EngineSystem/Entity/StateMachine.h>

#include <Game/Level/Level.h>

namespace AI {

    class ZombieAI : public BaseAI {
    private:
        ZombieAI(const ZombieAI &other_);
        ZombieAI &operator=(const ZombieAI &other_);
    public:
        ZombieAI(int id, Entity::CharacterEntity *character_ = nullptr);
        virtual ~ZombieAI();

        virtual void update();
        virtual bool handleMessage(const Entity::Message& msg);

        std::unique_ptr< Entity::StateMachine<ZombieAI> > SM;
    };

}

#endif // GAME_AI_ZOMBIEAI_H_INCLUDED
