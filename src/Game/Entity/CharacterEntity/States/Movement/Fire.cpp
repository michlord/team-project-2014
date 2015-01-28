#include <EngineSystem/Entity/MessageDispatcher.h>
#include <Game/Entity/CharacterEntity/States.h>
#include <Game/Entity/Spells/SpellEntity.h>

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
        castSpell(entity);
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
        (void)entity;
    }

    bool Fire::onMessage(CharacterEntity *entity, const Message &msg){
        (void) entity;
        (void) msg;

        return true;
    }

    void Fire::castSpell(CharacterEntity *entity) {
        if(entity->spells.size() > 0) {
            sf::Vector2f pos = entity->getFeetPosition();
            pos.y -= 48;
            pos.x += (entity->flipped ? -64 : 0);
            Entity::Spells::Spell* spell = new Entity::Spells::Spell(entity->spells[0], pos, entity->level, entity->flipped);
            entity->castedSpells.push_back(std::shared_ptr<Entity::Spells::Spell>(spell));
            entity->spells.erase(entity->spells.begin());
            entity->updateHUD();
        }
    }
}
