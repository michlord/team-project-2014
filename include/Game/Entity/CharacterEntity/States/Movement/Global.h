#ifndef GAME_ENTITY_CHARACTERENTITY_STATES_MOVEMENT_GLOBAL_H_INCLUDED
#define GAME_ENTITY_CHARACTERENTITY_STATES_MOVEMENT_GLOBAL_H_INCLUDED

#include <Game/Entity/CharacterEntity/CharacterEntity.h>
#include <EngineSystem/Entity/State.h>
#include <EngineApp/FrameContext.h>

namespace Entity {

    class Global : public State<CharacterEntity> {
    private:
    public:
        void onEnter(CharacterEntity *entity);
        void onUpdate(CharacterEntity *entity);
        void onExit(CharacterEntity *entity);
        bool onMessage(CharacterEntity *entity, const Message &msg);
    };

}

#endif // GAME_ENTITY_CHARACTERENTITY_STATES_MOVEMENT_GLOBAL_H_INCLUDED
