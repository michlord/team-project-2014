#ifndef GAME_HUD_HUD_H_INCLUDED
#define GAME_HUD_HUD_H_INCLUDED

#include <Game/Entity/Spells/SpellEntity.h>
#include <EngineApp/FrameContext.h>
#include <EngineSystem/Entity/BaseEntity.h>
#include <EngineSystem/Entity/Message.h>
#include <EngineSystem/Video/Render/Sprite.h>

namespace HUD {

    struct HudMsgData {
        unsigned life;
        Entity::Spells::SpellType spells[4];
    };

    class HUD : public Entity::BaseEntity
    {
    public:
        HUD();
        ~HUD();

        void setLife(const int life_);
        virtual void update();
        virtual bool handleMessage(const Entity::Message& msg);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
    protected:
        void init();

        Video::Render::Sprite* lifeGradient;
        Video::Render::Sprite* hudBackground;
        Video::Render::Sprite* spellsIcon[4];
        int life;
        Entity::Spells::SpellType spells[4];
    };
}

#endif /* GAME_HUD_HUD_H_INCLUDED */