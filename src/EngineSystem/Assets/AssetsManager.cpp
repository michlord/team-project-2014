#include "EngineSystem/Assets/AssetsManager.h"

namespace Assets {
    
    AssetsManager::AssetsManager() { 
        initDefaultPlaceholder(); 
    }

    AssetsManager::~AssetsManager() {
    }

    bool AssetsManager::loadTexture(const std::string& fileName, const std::string& id) {
        TexturePtr texture = TexturePtr(new sf::Texture());
        
        if(textures.find(id) != textures.end()) {
            Log::get().write(Log::System::Assets, "Texture id=%s already loaded.", id.c_str());
            return false;
        }

        if(!texture->loadFromFile(fileName)) {
            Log::get().write(Log::System::Assets, 
                "Couldn't load %s. Added placeholder as texture with id=%s.", fileName.c_str(), id.c_str());
            texture->loadFromImage(placeHolderImg);
            texture->setRepeated(true);
            textures.insert(std::make_pair(id, std::move(texture)));
            return false;
        }

        textures.insert(std::make_pair(id, std::move(texture)));
        Log::get().write(Log::System::Assets, "Added texture with id = %s (%s)", id.c_str(), fileName.c_str());
        return true;
    }

    bool AssetsManager::loadFont(const std::string& fileName, const std::string& id) { 
        FontPtr font = FontPtr(new sf::Font);

        if(fonts.find(id) != fonts.end()) {
            Log::get().write(Log::System::Assets, "Font id=%s already loaded.", id.c_str());
            return false;
        }

        if(!font->loadFromFile(fileName)) {
            font = FontPtr(new sf::Font(defaultFont));
            fonts.insert(std::make_pair(id, std::move(font)));
            Log::get().write(Log::System::Assets, 
                "Couldn't load %s. Added default font as font with id=%s.", fileName.c_str(), id.c_str());
            return false;
        }

        fonts.insert(std::make_pair(id, std::move(font)));
        Log::get().write(Log::System::Assets, "Added font with id = %s (%s)", id.c_str(), fileName.c_str());
        return true;
    }

    bool AssetsManager::setPlaceholder(const std::string& fileName) {
        sf::Image img;
                
        if(!img.loadFromFile(fileName)) {
            Log::get().write(Log::System::Assets, "Couldn't load %s as placeholder.", fileName.c_str());
            return false;
        } else
            Log::get().write(Log::System::Assets, "Loaded %s as texture placeholder.", fileName.c_str());

        placeHolderImg = img;
        texturePlaceholder.loadFromImage(placeHolderImg);
        texturePlaceholder.setRepeated(true);
        return true;
    };

    bool AssetsManager::setDefaultFont(const std::string& fileName) {
        if(defaultFont.loadFromFile(fileName)) {
            Log::get().write(Log::System::Assets, "Loaded %s as default font.", fileName.c_str());
            return true;
        } else {
            Log::get().write(Log::System::Assets, "Couldn't load %s as default font.", fileName.c_str());
            return false;
        }
    }

    sf::Texture& AssetsManager::getTexture(const std::string& id) {
        auto it = textures.find(id);

        if(it == textures.end()) {
            Log::get().write(Log::System::Assets, "Texture with id=%s is not loaded.", id.c_str());
            return texturePlaceholder;
        } else
            return *(it->second);
    }

    sf::Font& AssetsManager::getFont(const std::string& id) {
        auto it = fonts.find(id);

        if(it == fonts.end()) {
            Log::get().write(Log::System::Assets, "Font with id=%s is not loaded.", id.c_str());
            return defaultFont;
        } else
            return *(it->second);
    }

    void AssetsManager::initDefaultPlaceholder() {
        placeHolderImg.create(TEXTURE_PLACEHOLDER_SIZE, TEXTURE_PLACEHOLDER_SIZE, sf::Color(200, 200, 200));
        for(unsigned i = 0 ; i < TEXTURE_PLACEHOLDER_SIZE ; i++) {
            placeHolderImg.setPixel(i, 0, sf::Color::Red);
            placeHolderImg.setPixel(0, i, sf::Color::Red);
            placeHolderImg.setPixel(TEXTURE_PLACEHOLDER_SIZE-1, i, sf::Color::Red);
            placeHolderImg.setPixel(i, TEXTURE_PLACEHOLDER_SIZE-1, sf::Color::Red);
            placeHolderImg.setPixel(i, i, sf::Color::Red);
            placeHolderImg.setPixel(i, TEXTURE_PLACEHOLDER_SIZE-i-1, sf::Color::Red);
        }
        texturePlaceholder.loadFromImage(placeHolderImg);
        texturePlaceholder.setRepeated(true);
    }
} 