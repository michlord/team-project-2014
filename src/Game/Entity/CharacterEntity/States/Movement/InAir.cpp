#include <Game/Entity/CharacterEntity/States.h>

namespace Entity {

    void InAir::onEnter(CharacterEntity *entity){
        (void) entity;
    }

    void InAir::onUpdate(CharacterEntity *entity){
        (void) entity;

        
    }

    void InAir::onExit(CharacterEntity *entity){
        (void) entity;
    }

    bool InAir::onMessage(CharacterEntity *entity, const Message &msg){
        (void) entity; (void) msg;
        return true;
    }

}
