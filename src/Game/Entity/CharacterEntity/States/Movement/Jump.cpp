#include <Game/Entity/CharacterEntity/States.h>

namespace Entity {

    void Jump::onEnter(CharacterEntity *entity){
        (void) entity;
        entity->animation.setCurrentSequence("jump");
    }

    void Jump::onUpdate(CharacterEntity *entity){
        (void) entity;
    }

    void Jump::onExit(CharacterEntity *entity){
        (void) entity;
    }

    bool Jump::onMessage(CharacterEntity *entity, const Message &msg){
        (void) entity; (void) msg;
        return true;
    }

}
