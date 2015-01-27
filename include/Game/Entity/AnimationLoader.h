#ifndef GAME_ENTITY_ANIMATIONLOADER_H_INCLUDED
#define GAME_ENTITY_ANIMATIONLOADER_H_INCLUDED

#include <EngineSystem/Video/Render/Animation.h>

#include <string>
#include <memory>

namespace Entity {

    class AnimationLoader {
        public:
            static Video::Render::Animation loadAnimation(const std::string& animationFilePath, const sf::Texture& texture);
            static std::map<std::string, sf::FloatRect> loadCollision(const std::string& collisionFilePath);

    };

}


#endif