#include <Game/Entity/CharacterEntity/States.h>

#include <sfml/Audio.hpp>

namespace Entity {

    void Jump::onEnter(CharacterEntity *entity){
        static sf::SoundBuffer buffer;
        static sf::Sound sound;
        static bool initializedSound = false;

        if(initializedSound == false) {
            initializedSound = true;

            if(!buffer.loadFromFile("assets/sound/player_jump.wav")) {
                Log::get().write(Log::System::Game, "Could not load sound player_jump.wav");
            } else {
                sound.setBuffer(buffer);
            }
        }

        sound.play();
        entity->animation.setCurrentSequence("jump");
        currentJumpHeight = 0.0f;
    }

    void Jump::onUpdate(CharacterEntity *entity){
        if(!entity->animation.getSequence("jump")->isFinished()) {
            entity->animation.update(sf::seconds(Core::frameContext.deltaTime));
        }

        sf::Vector2f delta;
        if(entity->level->isRectCollidingWithWall(entity->getCurrentCollisionRect(), sf::Vector2f(0.0f, -1.0f), &delta)) {
            entity->setFeetPosition(entity->getFeetPosition() + delta);
            currentJumpHeight = entity->jumpHeight;
        } else {
            entity->setFeetPosition(entity->getFeetPosition() - sf::Vector2f(0.0f, 5.0f));
            currentJumpHeight += 5.0f;
        }

        if(currentJumpHeight >= entity->jumpHeight) {
            entity->movementSM->changeState(new Fall());
            return;
        }
    }

    void Jump::onExit(CharacterEntity *entity){
        (void) entity;
    }

    bool Jump::onMessage(CharacterEntity *entity, const Message &msg){
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
                        }
                        entity->setFeetPosition(entity->getFeetPosition() - sf::Vector2f(entity->runSpeed, 0));

                        return true;
                    }
                    case Input::ID::Right : {
                        entity->flipped = false;

                        sf::Vector2f delta;
                        if(entity->level->isRectCollidingWithWall(entity->getCurrentCollisionRect(), sf::Vector2f(1.0f, 0.0f), &delta)) {
                            entity->setFeetPosition(entity->getFeetPosition() + delta);
                        }
                        entity->setFeetPosition(entity->getFeetPosition() + sf::Vector2f(entity->runSpeed, 0));

                        return true;
                    }
                    case Input::ID::Space : {
                        if(entity->jumpCount + 1 < entity->maxJumps) {
                            entity->jumpCount += 1;
                            entity->movementSM->changeState(new Jump());
                            return true;
                        }
                    }
                    default : break;
                }
            } else {
                //this won't work because input action doesn't trigger when key is released.
                if(id == Input::ID::Space) {
                    if(currentJumpHeight < 50.0f) {
                        currentJumpHeight = entity->jumpHeight - currentJumpHeight;
                    } else {
                        currentJumpHeight = entity->jumpHeight;
                    }
                    return true;
                }
            }
        }

        return false;
    }

}
