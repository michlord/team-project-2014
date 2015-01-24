#include <Game/Entity/CharacterEntity/States.h>

namespace Entity {

    void Global::onEnter(CharacterEntity *entity){
        (void) entity;
    }

    void Global::onUpdate(CharacterEntity *entity){
        (void) entity;
    }

    void Global::onExit(CharacterEntity *entity){
        (void) entity;
    }

    bool Global::onMessage(CharacterEntity *entity, const Message &msg){
        (void) entity; (void) msg;
        return false;
    }

}
