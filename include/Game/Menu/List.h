#ifndef GAME_MENU_LIST_H_INCLUDED
#define GAME_MENU_LIST_H_INCLUDED

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <EngineSystem/Input/Input.h>
#include <EngineSystem/Sound/SoundManager.h>


namespace Menu {

    class ListItem;
    
    class List : public sf::Drawable {
        private:
            std::vector<ListItem> store;
            int                   curIdx; //tells which ListItem is focused
            
            sf::Vector2f          position;
            const sf::Font       *textFont;
            
        public:
            List(const sf::Font *_textFont, float posx = 0.0f, float posy = 0.0f);
            void setPosition(float x, float y);
            void draw(sf::RenderTarget &target, sf::RenderStates states) const;
            void handleInput(const Input::Input &in);
            const sf::Font& getFont();
            void addListItem(const ListItem& item);
            std::vector<ListItem>& getStore();
    };

}

#include "ListItem.h"

#endif // GAME_MENU_LIST_H_INCLUDED