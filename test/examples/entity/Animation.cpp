#include "Animation.h"

#include <SFML/System.hpp>

void Animation::update(float delta) {
    if(currentSequence) {
        currentSequence->setPosition(position);
        currentSequence->setSize(size);
        currentSequence->update(sf::seconds(delta));
    }
}

void Animation::draw(sf::RenderWindow* windowHandle) {
    if(currentSequence) {
        currentSequence->draw(windowHandle);
    }
}

void Animation::addAnimation(const char * name, const AnimatedSprite &sequence) {
    sequences[name] = sequence;
}

void Animation::setAnimation(const char *name) {
    auto it = sequences.find(name);
    if(it != sequences.end()) {
        currentSequenceName = name;
        currentSequence = &(it->second);
    }
}

AnimatedSprite * Animation::getCurrentSequence() {
    return currentSequence;
}

void Animation::setSize(unsigned int width, unsigned int height) {
    size = sf::Vector2u(width, height);
}

void Animation::setPosition(float positionX, float positionY) {
    position = sf::Vector2f(positionX, positionY);
}

Animation::Animation()
 : currentSequence(nullptr)
{
    
}

Animation::Animation(const Animation& other) {
    currentSequenceName = other.currentSequenceName;
    sequences = other.sequences;
    size = other.size;
    position = other.position;
    setAnimation(currentSequenceName.c_str());
}

Animation & Animation::operator=(const Animation& other) {
    currentSequenceName = other.currentSequenceName;
    sequences = other.sequences;
    size = other.size;
    position = other.position;
    setAnimation(currentSequenceName.c_str());
    return *this;
}