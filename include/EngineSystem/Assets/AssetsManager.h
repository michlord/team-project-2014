#ifndef ENGINE_SYSTEM_ASSETS_ASSETS_MANAGER_H_INCLUDED
#define ENGINE_SYSTEM_ASSETS_ASSETS_MANAGER_H_INCLUDED

#include <iostream>
#include <memory>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <unordered_map>
#include <utility>
#include <string>
#include <EngineSystem/Log/Log.h>

namespace Assets {
    const unsigned TEXTURE_PLACEHOLDER_SIZE = 100;

    class AssetsManager {
        public:
            AssetsManager();
            virtual ~AssetsManager();
    
            bool loadTexture(const std::string& fileName, const std::string& id);
            bool loadFont(const std::string& fileName, const std::string& id);

            bool setPlaceholder(const std::string& fileName);
            bool setDefaultFont(const std::string& fileName);

            sf::Texture& getTexture(const std::string& id);
            sf::Font&    getFont(const std::string& id);

        protected:
            typedef std::unique_ptr<sf::Texture> TexturePtr;
            typedef std::unique_ptr<sf::Font>    FontPtr;

        protected:
            std::unordered_map<std::string, TexturePtr> textures;
            std::unordered_map<std::string, FontPtr>    fonts;

            sf::Font defaultFont;
            sf::Image placeHolderImg;
            sf::Texture texturePlaceholder;

        protected:
            void initDefaultPlaceholder();
    };
}

#endif // ENGINE_SYSTEM_ASSETS_ASSETS_MANAGER_H_INCLUDED