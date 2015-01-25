#include <EngineSystem/Entity/MessageDispatcher.h>
#include <Game/Entity/CharacterEntity/States.h>

#include <sfml/Audio.hpp>

namespace Entity {

    void Fire::onEnter(CharacterEntity *entity){
        static sf::SoundBuffer buffer;
        static sf::Sound sound;
        static bool initializedSound = false;

        if(initializedSound == false) {
            initializedSound = true;

            if(!buffer.loadFromFile("assets/sound/player_shot.wav")) {
                Log::get().write(Log::System::Game, "Could not load sound player_shot.wav");
            } else {
                sound.setBuffer(buffer);
            }
        }

        sound.play();
        entity->animation.setCurrentSequence("cast");
    }

    void Fire::onUpdate(CharacterEntity *entity){
        entity->animation.update(sf::seconds(Core::frameContext.deltaTime));

        if(entity->animation.getSequence("cast")->isFinished()) {
            entity->movementSM->changeState(new Idle());
            entity->animation.getSequence("cast")->resetFinished();
            return;
        }
    }

    void Fire::onExit(CharacterEntity *entity){
        (void) entity;
    }

    bool Fire::onMessage(CharacterEntity *entity, const Message &msg){
        (void) entity;
        (void) msg;

        return true;
    }

}
