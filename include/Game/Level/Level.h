#ifndef GAME_LEVEL_LEVEL_H_INCLUDED
#define GAME_LEVEL_LEVEL_H_INCLUDED

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <Game/Level/Tile.h>
#include <Game/Level/Decoration.h>

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

            const std::list<Decoration>& getDecorations() const;
            //const std::list<Entity> getEntities() const;
            const std::vector<std::vector<Tile>>& getTiles() const;
 
        private:
            std::list<Decoration> decorations;
            //std::list<Entity> entities;
            std::vector<std::vector<Tile>> tiles;
    };

}

#endif