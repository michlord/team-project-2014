#include <Game/Entity/CharacterEntity/States.h>

namespace Entity {

    void InAir::onEnter(CharacterEntity *entity){
        (void) entity;
    }

    void InAir::onUpdate(CharacterEntity *entity){
        (void) entity;
        if(sf::Vector2f(0, 0) != entity->level->checkPlayerFeetTilesCollision(entity->getFeetPosition(), sf::Vector2f(0.0f, -1.0f))) {
            entity->movementSM->changeState(new Idle());
            entity->globalMovementSM->changeState(new OnGround());
            entity->jumpCount = 0;
        }
    }

    void InAir::onExit(CharacterEntity *entity){
        (void) entity;
    }

    bool InAir::onMessage(CharacterEntity *entity, const Message &msg){
        (void) entity; (void) msg;
        return true;
    }

}
