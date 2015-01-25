#ifndef GAME_ENTITY_CHARACTERENTITY_STATES_MOVEMENT_FIRE_H_INCLUDED
#define GAME_ENTITY_CHARACTERENTITY_STATES_MOVEMENT_FIRE_H_INCLUDED

#include <Game/Entity/CharacterEntity/CharacterEntity.h>
#include <EngineSystem/Entity/State.h>
#include <EngineApp/FrameContext.h>

namespace Entity {

    class Fire : public State<CharacterEntity> {

        public:
            void onEnter(CharacterEntity *entity);
            void onUpdate(CharacterEntity *entity);
            void onExit(CharacterEntity *entity);
            bool onMessage(CharacterEntity *entity, const Message &msg);

        private:

    };

}

#endif
