#ifndef GAME_AI_BASEAI_H_INCLUDED
#define GAME_AI_BASEAI_H_INCLUDED

#include <EngineSystem/Entity/BaseEntity.h>
#include <EngineSystem/Input/Input.h>

#include <Game/Entity/CharacterEntity/CharacterEntity.h>


namespace AI {

    class BaseAI : public Entity::BaseEntity {
    private:
        BaseAI(const BaseAI &other_);
        BaseAI &operator=(const BaseAI &other_);
    public:
        BaseAI(int id, Entity::CharacterEntity *character_ = nullptr);
        virtual ~BaseAI();

        virtual void update() = 0;
        virtual bool handleMessage(const Entity::Message& msg) = 0;

        Entity::CharacterEntity *character;
        Entity::CharacterEntity *player;
    };

}

#endif // GAME_AI_BASEAI_H_INCLUDED
