#include <EngineSystem/Entity/EntityManager.h>
#include <EngineSystem/Entity/MessageDispatcher.h>
#include <EngineSystem/Log/Log.h>
#include <Game/Level/Level.h>
#include <EngineSystem/Physics/Physics.h>
#include <Game/Entity/EntityDispatcher.h>
#include <Game/Entity/Door.h>
#include <EngineApp/FrameContext.h>

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
        for (auto& entity : getEntities())
            delete entity;
    }

    void Level::loadFromFile(unsigned int id, const std::string& path, Entity::EntityDispatcher* dispatcher) {
        sf::Image tilesImg;
        sf::Color tileColor;

        // Tiles
        tilesImg.loadFromFile(path + ".bmp");
        tiles.resize(tilesImg.getSize().y);

        for (unsigned int y = 0; y < tilesImg.getSize().y; ++y) {
            tiles[y].resize(tilesImg.getSize().x);

            for (unsigned int x = 0; x < tilesImg.getSize().x; ++x) {
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
        loadEntitiesFromFile(path + ".ent", dispatcher);

        (void)id;
    }

    void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        // Decorations
        for (auto& decoration : decorations)
            target.draw(decoration, states);

        // Tiles
        int startX, endX;
        int startY, endY;

        startX = static_cast<int>(Core::frameContext.window->getView().getCenter().x / 32.0f) - 10;
        startY = static_cast<int>(Core::frameContext.window->getView().getCenter().y / 32.0f) - 10;

        startX = std::max(startX, 0);
        startY = std::max(startY, 0);

        endX = startX + 20;
        endY = startY + 20;

        endY = std::min(endY, static_cast<int>(tiles.size()));
        endX = (tiles.size() > 0u) ? std::min(endX, static_cast<int>(tiles[0].size())) : 0;

        for (int y = startY; y < endY; ++y) {
            for (int x = startX; x < endX; ++x) {
                target.draw(tiles[y][x], states);
            }
        }

        // Entities
        for (auto& entity : entities)
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


    sf::Vector2f Level::checkPlayerFeetTilesCollision(sf::Vector2f feetPosition, sf::Vector2f dir) {
        std::vector<std::vector<Tile>>& tiles2dVec = getTiles();
        sf::Vector2f result;

        for (auto tilesVec : tiles2dVec)
        {
            for (auto tile : tilesVec)
            {
                if (tile.getType() == Tile::Type::Empty) continue;

                result = Physics::checkCollision(feetPosition, sf::FloatRect(tile.getPosition().x, tile.getPosition().y + 32, 32, 32), dir);

                if (result != sf::Vector2f(0.0, 0.0))
                    return result;
            }
        }

        return sf::Vector2f(0.0, 0.0);
    }

    sf::Vector2f Level::checkPlayerRectTilesCollision(sf::FloatRect playerRect, sf::Vector2f dir) {
        std::vector<std::vector<Tile>>& tiles2dVec = getTiles();
        sf::Vector2f result;

        for (auto tilesVec : tiles2dVec)
        {
            for (auto tile : tilesVec)
            {
                if (tile.getType() == Tile::Type::Empty) continue;

                result = Physics::checkCollision(playerRect, dir, sf::FloatRect(tile.getPosition().x, tile.getPosition().y + 32, 32, 32));

                if (result != sf::Vector2f(0.0, 0.0))
                    return result;
            }
        }

        return sf::Vector2f(0.0, 0.0);
    }

    bool Level::isFeetOnGround(sf::Vector2f feet, sf::Vector2f *delta) {
        auto& tiles = getTiles();
        unsigned x = static_cast<int>(feet.x / 32);
        unsigned y = static_cast<int>(feet.y / 32);
        if (y >= tiles.size() || x >= tiles[y].size())
            return false;
        auto tile = tiles[y][x];

        if (tile.getType() != Tile::Type::Empty) {
            sf::FloatRect tileRect(tile.getPosition(), tile.getSize());
            if (tileRect.contains(feet)) {
                if (delta) {
                    *delta = sf::Vector2f(0.0f, tileRect.top - feet.y);
                }
                return true;
            }
        }

        return false;
    }

    bool Level::isRectCollidingWithWall(sf::FloatRect rect, sf::Vector2f direction, sf::Vector2f *delta) {
        (void)rect; (void)direction; (void)delta;

        sf::Vector2f rectCenter(rect.left + rect.width / 2, rect.top + rect.height / 2);
        auto tiles = getTilesInRect(rect);

        for (auto tile : tiles) {
            if (tile.getType() == Tile::Type::Empty) {
                continue;
            }

            sf::FloatRect tileRect(tile.getPosition(), tile.getSize());
            sf::FloatRect intersection;

            if (tileRect.intersects(rect, intersection)) {
                //if going up
                if (direction.y < -0.5f && intersection.top < rectCenter.y && intersection.height < 16.0f && intersection.width > 10.f) {
                    if (delta) {
                        *delta = sf::Vector2f(0.0f, intersection.height);
                    }
                    return true;
                }
                //if going right
                if (direction.x > 0.5f && intersection.left > rectCenter.x && intersection.height > 16.0f) {
                    if (delta) {
                        *delta = sf::Vector2f(-intersection.width, 0.0f);
                    }
                    return true;
                }
                //if going left
                if (direction.x < -0.5f && intersection.left < rectCenter.x && intersection.height > 16.0f) {
                    if (delta) {
                        *delta = sf::Vector2f(intersection.width, 0.0f);
                    }
                    return true;
                }
            }

        }

        return false;
    }

    void Level::checkEndOfLevelCondition() {
        Entity::Door* door = dynamic_cast<Entity::Door*>(
            Entity::EntityManager::getInstance().getEntityById((int)Entity::EntityType::Door));
        Entity::CharacterEntity* player = dynamic_cast<Entity::CharacterEntity*>(
            Entity::EntityManager::getInstance().getEntityById((int)Entity::EntityType::Player));

        if (player && door && player->getCurrentCollisionRect().intersects(door->boundingRect)) {
            Entity::MessageDispatcher::getInstance().registerMessage(0, door->getId(), Entity::Door::Msg::NextLvl);
        }
    }

    void Level::setTile(Tile& tile, const sf::Color& color, int posX, int posY) {
        tile.setPosition(sf::Vector2f(static_cast<float>(posX), static_cast<float>(posY)));

        if (color == sf::Color::White) {
            tile.setType(Tile::Type::Empty);

        }
        else if (color == sf::Color::Black) {
            tile.setType(Tile::Type::Brick);
        }
        else if (color == sf::Color::Red) {
            tile.setType(Tile::Type::Spikes);
        }
        else {
            Log::get().write(Log::System::Game, "Unrecognized tile type (color): R(%u) G(%u) B(%u)", color.r, color.g, color.b);
        }
    }

    void Level::loadDecorationsFromFile(const std::string& path) {
        std::ifstream file;
        std::string decX, decY, decScale, decID;

        file.open(path);
        if (file.is_open() == false) {
            Log::get().write(Log::System::Game, "Could not open decorations file: %s", path.c_str());
            return;
        }

        while (file.good()) {

            file >> decX >> decY >> decScale >> decID;
            try {
                float posX = std::stof(decX);
                float posY = std::stof(decY);
                float scale = std::stof(decScale);

                decorations.push_back(Decoration(posX, posY, scale, decID));

            }
            catch (const std::invalid_argument& exception) {
                Log::get().write(Log::System::Game, "Unable to convert position data to numeric data (IA): X(%s), Y(%s), L(%s) (%s)",
                    decX.c_str(), decY.c_str(), decScale.c_str(), exception.what());

            }
            catch (const std::out_of_range& exception) {
                Log::get().write(Log::System::Game, "Unable to convert position data to numeric data (OOR): X(%s), Y(%s), L(%s) (%s)",
                    decX.c_str(), decY.c_str(), decScale.c_str(), exception.what());
            }
        }

        file.close();
    }

    void Level::loadEntitiesFromFile(const std::string& path, Entity::EntityDispatcher* dispatcher) {
        std::ifstream file;
        std::string entX, entY, entID;

        file.open(path);
        if (file.is_open() == false) {
            Log::get().write(Log::System::Game, "Could not open entities file: %s", path.c_str());
            return;
        }

        while (file.good()) {

            file >> entX >> entY >> entID;
            try {
                float posX = std::stof(entX);
                float posY = std::stof(entY);

                if (dispatcher == nullptr) {
                    Log::get().write(Log::System::Game, "Attempt to load entity without proper dispatcher!");
                }
                else {
                    dispatcher->createEntity(posX, posY, entID);
                }

            }
            catch (const std::invalid_argument& exception) {
                Log::get().write(Log::System::Game, "Unable to convert position data to numeric data (IA): X(%s), Y(%s) (%s)",
                    entX.c_str(), entY.c_str(), exception.what());

            }
            catch (const std::out_of_range& exception) {
                Log::get().write(Log::System::Game, "Unable to convert position data to numeric data (OOR): X(%s), Y(%s) (%s)",
                    entX.c_str(), entY.c_str(), exception.what());
            }
        }

        file.close();
    }

    std::vector<Tile> Level::getTilesInRect(const sf::FloatRect rect) {
        auto& tiles = getTiles();

        std::vector<Tile> res;
        unsigned x_start = static_cast<int>(rect.left / 32);
        unsigned y_start = static_cast<int>(rect.top / 32);
        unsigned x_end = static_cast<int>(ceil((rect.left + rect.width) / 32));
        unsigned y_end = static_cast<int>(ceil((rect.top + rect.height) / 32));

        for (unsigned x = x_start; x < x_end; x++)
        for (unsigned y = y_start; y < y_end; y++)
        if (y < tiles.size() && x < tiles[y].size())
            res.push_back(tiles[y][x]);
        return res;
    }


    Tile::Type Level::getTileOnFeet(sf::Vector2f feetPosition) {
        auto& tiles = getTiles();
        unsigned x = static_cast<int>(feetPosition.x / 32);
        unsigned y = static_cast<int>(feetPosition.y / 32);
        if (y >= tiles.size() || x >= tiles[y].size())
            return Tile::Type::Empty;

        auto tile = tiles[y][x];

        return tile.getType();
    }
}