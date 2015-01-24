#ifndef GAME_LEVEL_LEVEL_H_INCLUDED
#define GAME_LEVEL_LEVEL_H_INCLUDED

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <Game/Level/Tile.h>
#include <Game/Level/Decoration.h>
#include <EngineSystem/Entity/BaseEntity.h>

#include <list>
#include <vector>

namespace Entity {
    class EntityDispatcher;
}

namespace Level {

    class Level : public sf::Drawable {
        public:
            Level();
            Level(unsigned int id, const std::string& path);
            ~Level();

            void loadFromFile(unsigned int id, const std::string& path, Entity::EntityDispatcher* dispatcher = nullptr);

            void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;

            unsigned int getID() const;
            std::list<Decoration>& getDecorations();
            std::list<Entity::BaseEntity*>& getEntities();
            std::vector<std::vector<Tile>>& getTiles();

            void setID(unsigned int id_);
            sf::Vector2f checkPlayerFeetTilesCollision(sf::Vector2f feetPosition, sf::Vector2f dir);
            sf::Vector2f checkPlayerRectTilesCollision(sf::FloatRect playerRect, sf::Vector2f dir);
            
            bool isFeetOnGround(sf::Vector2f feet, sf::Vector2f *delta = nullptr);
            bool isRectCollidingWithWall(sf::FloatRect rect, sf::Vector2f direction, sf::Vector2f *delta = nullptr);

        private:
            void setTile(Tile& tile, const sf::Color& color, int posX, int posY);
            void loadDecorationsFromFile(const std::string& path);
            void loadEntitiesFromFile(const std::string& path, Entity::EntityDispatcher* dispatcher = nullptr);

            unsigned int id;
            std::list<Decoration> decorations;
            std::list<Entity::BaseEntity*> entities;
            std::vector<std::vector<Tile>> tiles;
    };

}

#endif
