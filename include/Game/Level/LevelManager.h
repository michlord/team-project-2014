#ifndef GAME_LEVEL_LEVELMANAGER_H_INCLUDED
#define GAME_LEVEL_LEVELMANAGER_H_INCLUDED

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <EngineSystem/Video/Render/AnimatedSprite.h>
#include <Game/Level/Level.h>

#include <unordered_map>

namespace Level {

    class LevelManager {
        public:
            LevelManager();
            ~LevelManager();

            void addLevel(unsigned int levelID, const std::string& levelPath);
            void loadLevel(unsigned int levelID);
            void resetLevel(); 
 
            Level& getCurrentLevel();
            const Level& getCurrentLevel() const;
            const std::unordered_map<unsigned int, std::string>& getLevels() const;
 
        private:
            unsigned int currentID;
            Level currentLevel;
            std::unordered_map<unsigned int, std::string> levels;
    };

}

#endif