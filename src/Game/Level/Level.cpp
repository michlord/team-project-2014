#include <Game/Level/Level.h>

namespace Level {

    Level::Level() {

    }

    Level::Level(unsigned int id, const std::string& path) {
        loadFromFile(id, path);
    }

    Level::~Level() {

    }
 
    void Level::loadFromFile(unsigned int id, const std::string& path) {
        path;
        id;

        //TODO: implement level loader
        //TODO: work-out level tile's layout
    }

    void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        // Tiles
        for(const std::vector<Tile>& tileVector : tiles) {
            for(const Tile& tile : tileVector) {
                tile.draw(target, states);
            }
        }

        // Decorations


        // Entities

    }

    const std::list<Decoration>& Level::getDecorations() const {
        return decorations;
    }

    //const std::list<Entity> Level::getEntities() const;

    const std::vector<std::vector<Tile>>& Level::getTiles() const {
        return tiles;
    }

}