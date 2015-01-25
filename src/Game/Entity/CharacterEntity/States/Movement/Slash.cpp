#include <EngineSystem/Entity/MessageDispatcher.h>
#include <Game/Entity/CharacterEntity/States.h>

#include <sfml/Audio.hpp>

namespace Entity {

    void Slash::onEnter(CharacterEntity *entity){
        static sf::SoundBuffer buffer;
        static sf::Sound sound;
        static bool initializedSound = false;

        if(initializedSound == false) {
            initializedSound = true;

            if(!buffer.loadFromFile("assets/sound/player_slash.wav")) {
                Log::get().write(Log::System::Game, "Could not load sound player_jump.wav");
            } else {
                sound.setBuffer(buffer);
            }
        }

        sound.play();
        entity->animation.setCurrentSequence("slash");
        enemyAttacked = false;
    }

    void Slash::onUpdate(CharacterEntity *entity){
        entity->animation.update(sf::seconds(Core::frameContext.deltaTime));
        if(entity->animation.getSequence("slash")->isFinished()) {
            entity->movementSM->changeState(new Idle());
            entity->animation.getSequence("slash")->resetFinished();
            return;
        }
    }

    void Slash::onExit(CharacterEntity *entity){
        (void) entity;
    }

    bool Slash::onMessage(CharacterEntity *entity, const Message &msg){
        if(msg.msg == Entity::CharacterEntity::EnemyCollision && false == enemyAttacked) {
            Entity::MessageDispatcher::getInstance().registerMessage(entity->getId(), msg.sender, Entity::CharacterEntity::Attacked);
            enemyAttacked = true;
        }
        return true;
    }

}
