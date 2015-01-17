#ifndef GAME_MENU_LISTITEM_H_INCLUDED
#define GAME_MENU_LISTITEM_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <functional>
#include <string>

#include <EngineSystem/Input/Input.h>



namespace Menu {

class List;

class ListItem : public sf::Drawable {
    private:
        List        *parent;
        sf::Vector2f position;
        bool         selected;
        bool         focused;
        int          value;
        std::string  label;
        bool         selectable;
        std::function<int(const Input::Input&, int)>  valueUpdateFun;
        std::function<std::string(int)>               valueTranslateFun;
    public:
        ListItem(List *_parent,
            const char *_label,
            int _value = 0,
            bool _selectable = false,
            std::function<int(const Input::Input&, int)> _valueUpdateFun = nullptr,
            std::function<std::string(int)> _valueTranslateFun = nullptr,
            float posx = 0.0f, float posy = 0.0f);
        
        void setPosition(float x, float y);
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        void handleInput(const Input::Input &in);
        bool isSelected();
        void setSelected(bool _selected);
        bool isFocused();
        void setFocused(bool _focused);
        bool isSelectable();
        void setValue(int _value);
        int  getValue();
};

}

#include "List.h"

#endif // GAME_MENU_LISTITEM_H_INCLUDED