#ifndef ENGINE_SYSTEM_GAME_ENTITY_DOOR_H_INCLUDED
#define ENGINE_SYSTEM_GAME_ENTITY_DOOR_H_INCLUDED

#include <EngineSystem/Entity/BaseEntity.h>
#include <EngineApp/FrameContext.h>
#include <Game/Level/LevelManager.h>
#include <EngineSystem/Entity/Message.h>
#include <EngineSystem/Assets/AssetsManager.h>
#include <EngineSystem/Video/Render/Sprite.h>

namespace Entity {

    class Door : public BaseEntity {
        public:
            enum Msg {
                NextLvl
            };

            sf::FloatRect boundingRect;
            Door(int id, sf::Vector2f pos);
            ~Door();
        
            bool handleMessage(const Message& msg);
            virtual void update();
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;

        private:
            Video::Render::Sprite *sprite;
    };
}


#endif
