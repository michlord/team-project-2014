#include <Game/Menu/List.h>
#include <EngineSystem/Input/BinaryInput.h>
#include <EngineSystem/Log/Log.h>

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
    static bool soundsInitialized = false;
    static sf::SoundBuffer bufferSoundMove;
    static sf::SoundBuffer bufferSoundSelect;
    static sf::Sound soundMove;
    static sf::Sound soundSelect;
    
    if(soundsInitialized == false) {
        soundsInitialized = true;

        if(!bufferSoundMove.loadFromFile("assets/sound/menu_move.ogg")) {
            Log::get().write(Log::System::Game, "Unable to load menu_move.ogg sound file!");
        } else {
            soundMove.setBuffer(bufferSoundMove);
        }

        if(!bufferSoundSelect.loadFromFile("assets/sound/menu_select.ogg")) {
            Log::get().write(Log::System::Game, "Unable to load menu_select.ogg sound file!");
        } else {
            soundSelect.setBuffer(bufferSoundSelect);
        }
    }

    if(const Input::BinaryInput *p = dynamic_cast<const Input::BinaryInput*>(&in)) {
        if(store.empty() || !p->isPressed()) {
            return;
        }
        if(p->getId() == Input::ID::Escape) {
            if(curIdx >= 0) {
                store[curIdx].setSelected(false);
            }
            return;
        }
        if(curIdx >= 0 && store[curIdx].isSelected()) {
            store[curIdx].handleInput(in);
            store[curIdx].setSelected(false);
            return;
        }
        if(p->getId() == Input::ID::Return) {
            soundSelect.play();

            if(curIdx >= 0) {
                if(store[curIdx].isSelectable()) {
                    store[curIdx].setSelected(true);
                } else {
                    store[curIdx].handleInput(in);
                }
            }
            return;
        }
        if(p->getId() == Input::ID::Down) {
            if(curIdx >= 0) {
                store[curIdx].setFocused(false);
            }
            curIdx = (curIdx + 1) % store.size();
            store[curIdx].setFocused(true);
            soundMove.play();
            return;
        }
        if(p->getId() == Input::ID::Up) {
            if(curIdx >= 0) {
                store[curIdx].setFocused(false);
            }
            if(curIdx <= 0) {
                curIdx = (int)store.size() - 1;
            } else {
                curIdx -= 1;
            }
            store[curIdx].setFocused(true);
            soundMove.play();
            return;
        }
    }
}

const sf::Font& List::getFont() {
    return *textFont;
}

void List::addListItem(const ListItem& item) {
    store.push_back(item);

    if(curIdx < 0) {
        curIdx = 0;
        store[curIdx].setFocused(true);
    }
}

std::vector<ListItem>& List::getStore() {
    return store;
}

}