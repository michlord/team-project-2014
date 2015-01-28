#include <Game/Entity/CharacterEntity/States.h>
#include <iostream>

namespace Entity {

    sf::SoundBuffer Run::soundBuffer;

    Run::Run() {
        static bool initializedBuffer = false;

        if(initializedBuffer == false) {
            initializedBuffer = true;
            if(!soundBuffer.loadFromFile("assets/sound/player_run.wav")) {
                Log::get().write(Log::System::Game, "Could not load sound player_run.wav");
            }
        }

        sound.setBuffer(soundBuffer);
    }

    void Run::onEnter(CharacterEntity *entity){
        entity->animation.setCurrentSequence("run");

        sound.play();
    }

    void Run::onUpdate(CharacterEntity *entity){
        entity->animation.update(sf::seconds(Core::frameContext.deltaTime));

        if(sound.getStatus() != sf::SoundSource::Status::Playing)
            sound.play();

        if(entity->flipped){
            sf::Vector2f delta;
            if(entity->level->isRectCollidingWithWall(entity->getCurrentCollisionRect(), sf::Vector2f(-1.0f, 0.0f), &delta)) {
                entity->setFeetPosition(entity->getFeetPosition() + delta);
            } else {
                entity->setFeetPosition(entity->getFeetPosition() - sf::Vector2f(entity->runSpeed, 0));
            }
        } else {
            sf::Vector2f delta;
            if(entity->level->isRectCollidingWithWall(entity->getCurrentCollisionRect(), sf::Vector2f(1.0f, 0.0f), &delta)) {
                entity->setFeetPosition(entity->getFeetPosition() + delta);
            } else {
                entity->setFeetPosition(entity->getFeetPosition() + sf::Vector2f(entity->runSpeed, 0));
            }
        }

    }

    void Run::onExit(CharacterEntity *entity){
        (void) entity;

        if(sound.getStatus() == sf::SoundSource::Status::Playing)
            sound.stop();
    }

    bool Run::onMessage(CharacterEntity *entity, const Message &msg){
        if(msg.msg == CharacterEntity::MessageType::Input) {
            Input::ID id = (Input::ID) msg.arg1;
            int pressed = msg.arg2;

            if(!pressed) {
                if(entity->flipped && id == Input::ID::Left) {
                    entity->movementSM->changeState(new Idle());
                    return true;
                }
                if(!entity->flipped && id == Input::ID::Right) {
                    entity->movementSM->changeState(new Idle());
                    return true;
                }
            } else {
                if(id == Input::ID::X) {
                    entity->movementSM->changeState(new Slash());
                    return true;
                }
            }
        }

        return false;
    }

}
