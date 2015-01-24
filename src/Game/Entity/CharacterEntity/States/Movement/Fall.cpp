#include <Game/Entity/CharacterEntity/States.h>

namespace Entity {

    void Fall::onEnter(CharacterEntity *entity){
        entity->animation.setCurrentSequence("fall");
    }

    void Fall::onUpdate(CharacterEntity *entity){
        entity->animation.update(sf::seconds(Core::frameContext.deltaTime));

        sf::Vector2f delta;
        if(entity->level->isFeetOnGround(entity->getFeetPosition(), &delta)) {
            entity->setFeetPosition(entity->getFeetPosition() + delta);
            entity->movementSM->changeState(new Idle());
            entity->globalMovementSM->changeState(new OnGround());
            entity->jumpCount = 0;
        } else {
            entity->setFeetPosition(entity->getFeetPosition() + sf::Vector2f(0.0f, 5.0f));
        }
    }

    void Fall::onExit(CharacterEntity *entity){
        (void) entity;
    }

    bool Fall::onMessage(CharacterEntity *entity, const Message &msg){
        if(msg.msg == CharacterEntity::MessageType::Input) {
            Input::ID id = (Input::ID) msg.arg1;
            int pressed = msg.arg2;

            if(pressed) {
                switch(id) {
                    case Input::ID::Left : {
                        entity->flipped = true;

                        sf::Vector2f delta;
                        if(entity->level->isRectCollidingWithWall(entity->getCurrentCollisionRect(), sf::Vector2f(-1.0f, 0.0f), &delta)) {
                            entity->setFeetPosition(entity->getFeetPosition() + delta);
                        } else {
                            entity->setFeetPosition(entity->getFeetPosition() - sf::Vector2f(3, 0));
                        }

                        return true;
                    }
                    case Input::ID::Right : {
                        entity->flipped = false;

                        sf::Vector2f delta;
                        if(entity->level->isRectCollidingWithWall(entity->getCurrentCollisionRect(), sf::Vector2f(1.0f, 0.0f), &delta)) {
                            entity->setFeetPosition(entity->getFeetPosition() + delta);
                        } else {
                            entity->setFeetPosition(entity->getFeetPosition() + sf::Vector2f(3, 0));
                        }

                        return true;
                    }
                    default : break;
                }
            }
        }
        return false;
    }

}
