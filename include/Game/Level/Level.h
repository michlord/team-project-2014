#ifndef GAME_LEVEL_LEVEL_H_INCLUDED
#define GAME_LEVEL_LEVEL_H_INCLUDED

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <Game/Level/Tile.h>
#include <Game/Level/Decoration.h>
#include <EngineSystem/Entity/BaseEntity.h>

#include <list>
#include <vector>

namespace Level {

    class Level : public sf::Drawable {
        public:
            Level();
            Level(unsigned int id, const std::string& path);
            ~Level();
 
            void loadFromFile(unsigned int id, const std::string& path);
            void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;

            std::list<Decoration>& getDecorations();
            std::list<Entity::BaseEntity*>& getEntities();
            std::vector<std::vector<Tile>>& getTiles();
 
        private:
            Tile getTileFromColor(const sf::Color& color, int posX, int posY);
            void loadDecorationsFromFile(const std::string& path);
            void loadEntitiesFromFile(const std::string& path);

            std::list<Decoration> decorations;
            std::list<Entity::BaseEntity*> entities;
            std::vector<std::vector<Tile>> tiles;
    };

}

#endif