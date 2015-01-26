#ifndef GAME_ENTITY_SPELLS_SPELLSOURCE_H_INCLUDED
#define GAME_ENTITY_SPELLS_SPELLSOURCE_H_INCLUDED

#include <EngineSystem/Entity/BaseEntity.h>
#include <EngineSystem/Video/Render/Sprite.h>
#include <Game/Entity/Spells/SpellEntity.h>

namespace Entity {
    namespace Spells {

        class SpellSource : public BaseEntity {
        public:
            SpellSource(int id, sf::Vector2f pos, const SpellType type_);
            ~SpellSource();
        
            bool handleMessage(const Message& msg);
            virtual void update();
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;

            SpellType getSpellType() const;

            sf::FloatRect boundingRect;
        private:

            Video::Render::Sprite *sprite;
            SpellType type;
    };
        
    }
}

#endif /* GAME_ENTITY_SPELLS_SPELLSOURCE_H_INCLUDED */