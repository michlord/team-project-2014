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
    }

    void Jump::onUpdate(CharacterEntity *entity){
        entity->animation.update(sf::seconds(Core::frameContext.deltaTime));
        entity->setFeetPosition(entity->getFeetPosition() - sf::Vector2f(0.0f, 5.0f));
        if(entity->animation.getSequence("jump")->isFinished()) {
            entity->movementSM->changeState(new Fall());
            entity->animation.getSequence("jump")->resetFinished();
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
                        entity->setFeetPosition(entity->getFeetPosition() - sf::Vector2f(3, 0));
                        return true;
                    }
                    case Input::ID::Right : {
                        entity->flipped = false;
                        entity->setFeetPosition(entity->getFeetPosition() + sf::Vector2f(3, 0));
                        return true;
                    }
                    case Input::ID::Space : {
                        if(entity->jumpCount < entity->maxJumps) {
                            entity->jumpCount += 1;
                            entity->movementSM->changeState(new Jump());
                            return true;
                        }
                    }
                    default : break;
                }
            }
        }

        return false;
    }

}
