#include <Game/Level/LevelManager.h>

namespace Level {

    LevelManager::LevelManager() {
        currentID = 0;
    }

    LevelManager::~LevelManager() {

    }

    void LevelManager::addLevel(unsigned int levelID, const std::string& levelPath) {
        levels[levelID] = levelPath;
    }

    void LevelManager::loadLevel(unsigned int levelID) {
        currentID = levelID;
        currentLevel.loadFromFile(levelID, levels[levelID]);
    }

    void LevelManager::resetLevel() {
        currentLevel.loadFromFile(currentID, levels[currentID]);
    }
 
    Level& LevelManager::getCurrentLevel() {
        return currentLevel;
    }

    const Level& LevelManager::getCurrentLevel() const {
        return currentLevel;
    }

    const std::unordered_map<unsigned int, std::string>& LevelManager::getLevels() const {
        return levels;
    }
 
}