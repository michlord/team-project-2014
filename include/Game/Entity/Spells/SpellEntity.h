#ifndef GAME_ENTITY_SPELLS_SPELLENTITY_H_INCLUDED
#define GAME_ENTITY_SPELLS_SPELLENTITY_H_INCLUDED

#include <EngineSystem/Entity/BaseEntity.h>
#include <EngineSystem/Video/Render/Animation.h>
#include <Game/Level/Level.h>

namespace Entity {

    class CharacterEntity;

    namespace Spells {

        enum SpellType {
            Fire,
            Nature,
            Wind,
            Ice,
            None
        };

        class Spell : public BaseEntity
        {
        public:
            Spell(const SpellType type_, const sf::Vector2f pos, Level::Level* level_, const bool flipped_ = false);
            ~Spell();

            bool handleMessage(const Message& msg);
            void update();
            void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
            sf::FloatRect getCurrentCollisionRect() const;
            bool isExpired();
            void setAsExpired(const bool expired_);
            void applyEffectOn(CharacterEntity* entity);

        private:
            Spell(const Spell &other_);
            Spell& operator=(const Spell &other_);
            void initAnimation();
            
            float speed;
            bool flipped;
            bool expired;
            sf::FloatRect boundingRect;
            SpellType type;
            Video::Render::Animation animation;
            Level::Level* level;
        };

    }
}

#endif /* GAME_ENTITY_SPELLS_SPELLENTITY_H_INCLUDED */