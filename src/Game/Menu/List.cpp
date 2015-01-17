#include <Game/Menu/List.h>
#include <EngineSystem/Input/BinaryInput.h>

namespace Menu {

List::List(const sf::Font *_textFont, float posx, float posy)
 : curIdx(-1), position(posx, posy), textFont(_textFont)
{
}

void List::setPosition(float x, float y) {
    position = sf::Vector2f(x, y);
}

void List::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform.translate(position);
    
    int spacing = textFont->getLineSpacing(30);
        
    for (size_t i = 0; i < store.size(); ++i) {
        const ListItem &item = store[i];
        target.draw(item, states);
        states.transform.translate(0.0f, (float) spacing);
    }
}

void List::handleInput(const Input::Input &in) {
    if(const Input::BinaryInput *p = dynamic_cast<const Input::BinaryInput*>(&in)) {
        if(store.empty() || !p->isPressed()) {
            return;
        }
        if(p->getId() == Input::ID::Down) {
            if(curIdx >= 0) {
                store[curIdx].setFocused(false);
            }
            curIdx = (curIdx + 1) % store.size();
            store[curIdx].setFocused(true);
        }
        if(p->getId() == Input::ID::Up) {
            if(curIdx >= 0) {
                store[curIdx].setFocused(false);
            }
            if(curIdx <= 0) {
                curIdx = store.size() - 1;
            } else {
                curIdx -= 1;
            }
            store[curIdx].setFocused(true);
        }
    }
}

const sf::Font& List::getFont() {
    return *textFont;
}

void List::addListItem(const ListItem& item) {
    store.push_back(item);
}

}