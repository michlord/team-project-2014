#include <Game/Menu/ListItem.h>


namespace Menu {

ListItem::ListItem(List *_parent,
    const char *_label,
    std::function<int(const Input::Input&, int)> _valueUpdateFun,
    std::function<std::string(int)> _valueTranslateFun,
    float posx, float posy)
 : parent(_parent), position(posx, posy), selected(false), focused(false),
   value(0), label(_label), valueUpdateFun(_valueUpdateFun), valueTranslateFun(_valueTranslateFun)
{
    if(!valueUpdateFun) {
        valueUpdateFun = [](const Input::Input &in, int val) {
            (void) in;
            return val;
        };
    }
    
    if(!valueTranslateFun) {
        valueTranslateFun = [](int val) {
            //return std::to_string(val);
            (void) val;
            return "";
        };
    }
    
    parent->addListItem(*this);
}
        
void ListItem::setPosition(float x, float y) {
    position = sf::Vector2f(x, y);
}

void ListItem::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    (void) states;
    sf::Text text;
    text.setFont(parent->getFont());
    text.setString(label + " " + valueTranslateFun(value));
    if (focused) {
        text.setColor(sf::Color::Yellow);
    }
    target.draw(text, states);
}

void ListItem::handleInput(const Input::Input &in) {
    value = valueUpdateFun(in, value);
}

bool ListItem::isSelected() {
    return selected;
}

void ListItem::setSelected(bool _selected) {
    selected = _selected;
}

bool ListItem::isFocused() {
    return focused;
}

void ListItem::setFocused(bool _focused) {
    focused = _focused;
}

}