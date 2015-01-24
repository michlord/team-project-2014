#ifndef GAME_LEVEL_LEVELMANAGER_H_INCLUDED
#define GAME_LEVEL_LEVELMANAGER_H_INCLUDED

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <EngineSystem/Video/Render/AnimatedSprite.h>
#include <Game/Level/Level.h>

#include <unordered_map>

namespace Entity {
    class EntityDispatcher;
}

namespace Level {

    class LevelManager {
        public:
            LevelManager();
            ~LevelManager();

            void initTextures();

            void addLevel(unsigned int levelID, const std::string& levelPath);
            void loadLevel(unsigned int levelID, Entity::EntityDispatcher* _dispatcher = nullptr);
            void resetLevel();

            Level& getCurrentLevel();
            unsigned int getCurrentID() const;
            const Level& getCurrentLevel() const;
            const std::unordered_map<unsigned int, std::string>& getLevels() const;

        private:
            unsigned int currentID;
            Level currentLevel;
            std::unordered_map<unsigned int, std::string> levels;

            Entity::EntityDispatcher* dispatcher;

    };

    extern LevelManager levelManager;

}



#endif
