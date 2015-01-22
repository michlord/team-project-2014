#include <Game/Level/LevelManager.h>
#include <EngineApp/FrameContext.h>
#include <EngineSystem/Assets/AssetsManager.h>

namespace Level {

    LevelManager levelManager = [](){
        LevelManager mgr;

        //Preload level data here.
        mgr.addLevel(0, "assets/levels/level0");

        return mgr;
    }();

    LevelManager::LevelManager() {
        currentID = 0;
    }

    LevelManager::~LevelManager() {

    }
    
    void LevelManager::initTextures() {
        Core::frameContext.assetsManager->loadTexture("assets/images/tiles_atlas.png", "tiles_atlas");
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

    unsigned int LevelManager::getCurrentID() const {
        return currentID;
    }

    const Level& LevelManager::getCurrentLevel() const {
        return currentLevel;
    }

    const std::unordered_map<unsigned int, std::string>& LevelManager::getLevels() const {
        return levels;
    }

}
