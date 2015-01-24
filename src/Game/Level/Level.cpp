#include <EngineSystem/Log/Log.h>
#include <Game/Level/Level.h>

#include <iostream>

namespace Level {

    Level::Level() {
        setID(0);
    }

    Level::Level(unsigned int id, const std::string& path) {
        loadFromFile(id, path);
        setID(id);
    }

    Level::~Level() {
        for(auto& entity : getEntities())
            delete entity;
    }

    void Level::loadFromFile(unsigned int id, const std::string& path) {
        sf::Image tilesImg;
        sf::Color tileColor;

        // Tiles
        tilesImg.loadFromFile(path + ".bmp");
        tiles.resize(tilesImg.getSize().y);

        for(unsigned int y = 0; y < tilesImg.getSize().y; ++y) {
            tiles[y].resize(tilesImg.getSize().x);

            for(unsigned int x = 0; x < tilesImg.getSize().x; ++x) {
                tileColor = tilesImg.getPixel(x, y);
                setTile(tiles[y][x], tileColor, x, y);
            }
        }

        // Decorations
        loadDecorationsFromFile(path + ".dec");
        decorations.sort([](const Decoration& a, const Decoration& b) {
            return a.getScale() > b.getScale();
        });

        // Entities
        loadEntitiesFromFile(path + ".ent");

        (void)id;
    }

    void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        // Decorations
        for(auto& decoration : decorations)
            target.draw(decoration, states);

        // Tiles
        for(auto& tileLine : tiles)
            for(auto& tile : tileLine)
                target.draw(tile, states);

        // Entities
        for(auto& entity : entities)
            target.draw(*entity, states);
    }

    unsigned int Level::getID() const {
        return id;
    }

    std::list<Decoration>& Level::getDecorations(){
        return decorations;
    }

    std::list<Entity::BaseEntity*>& Level::getEntities() {
        return entities;
    }

    std::vector<std::vector<Tile>>& Level::getTiles() {
        return tiles;
    }
    
    void Level::setID(unsigned int id_) {
        id = id_;
    }

    void Level::setTile(Tile& tile, const sf::Color& color, int posX, int posY) {
        tile.setPosition(sf::Vector2f(static_cast<float>(posX), static_cast<float>(posY)));

        if(color == sf::Color::White) {
            tile.setType(Tile::Type::Empty);

        } else if(color == sf::Color::Black) {
            tile.setType(Tile::Type::Brick);

        } else {
            Log::get().write(Log::System::Game, "Unrecognized tile type (color): R(%u) G(%u) B(%u)", color.r, color.g, color.b);
        }
    }

    void Level::loadDecorationsFromFile(const std::string& path) {
        std::ifstream file;
        std::string decX, decY, decScale, decID;

        file.open(path);
        if(file.is_open() == false) {
            Log::get().write(Log::System::Game, "Could not open decorations file: %s", path.c_str());
            return;
        }

        while(file.good()) {

            file >> decX >> decY >> decScale >> decID;
            try {
                float posX  = std::stof(decX);
                float posY  = std::stof(decY);
                float scale = std::stof(decScale);

                decorations.push_back(Decoration(posX, posY, scale, decID));

            } catch(const std::invalid_argument& exception) {
                Log::get().write(Log::System::Game, "Unable to convert position data to numeric data (IA): X(%s), Y(%s), L(%s) (%s)",
                    decX.c_str(), decY.c_str(), decScale.c_str(), exception.what());

            } catch(const std::out_of_range& exception) {
                Log::get().write(Log::System::Game, "Unable to convert position data to numeric data (OOR): X(%s), Y(%s), L(%s) (%s)",
                    decX.c_str(), decY.c_str(), decScale.c_str(), exception.what());
            }
        }

        file.close();
    }

    void Level::loadEntitiesFromFile(const std::string& path) {
        std::ifstream file;
        std::string entX, entY, entID;

        file.open(path);
        if(file.is_open() == false) {
            Log::get().write(Log::System::Game, "Could not open entities file: %s", path.c_str());
            return;
        }

        while(file.good()) {

            file >> entX >> entY >> entID;
            try {
                int posX = std::stoi(entX);
                int posY = std::stoi(entY);

                (void)posX;
                (void)posY;

                //TODO: something with loaded entity, i.e. add it to list or get object from some factory

            } catch(const std::invalid_argument& exception) {
                Log::get().write(Log::System::Game, "Unable to convert position data to numeric data (IA): X(%s), Y(%s) (%s)",
                    entX.c_str(), entY.c_str(), exception.what());

            } catch(const std::out_of_range& exception) {
                Log::get().write(Log::System::Game, "Unable to convert position data to numeric data (OOR): X(%s), Y(%s) (%s)",
                    entX.c_str(), entY.c_str(), exception.what());
            }
        }

        file.close();
    }

}
