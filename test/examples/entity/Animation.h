#ifndef TEST_ENTITY_ANIMATION_H_INCLUDED
#define TEST_ENTITY_ANIMATION_H_INCLUDED

#include <string>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <EngineSystem/Video/Render/Sprite.h>
#include <EngineSystem/Video/Render/AnimatedSprite.h>

using namespace Video::Render;

class Animation {
    private:
        std::string currentSequenceName;
        AnimatedSprite *currentSequence;
        std::map<std::string, AnimatedSprite> sequences;
        sf::Vector2u size;
        sf::Vector2f position;
    public:
        void update(float delta);
        void draw(sf::RenderWindow* windowHandle);
        void addAnimation(const char * name, const AnimatedSprite &sequence);
        void setAnimation(const char *name);
        AnimatedSprite * getCurrentSequence();
        void setSize(unsigned int width, unsigned int height);
        void setPosition(float positionX, float positionY);
        Animation();
        Animation(const Animation& other);
        Animation & operator=(const Animation& other);
};

#endif // TEST_ENTITY_ANIMATION_H_INCLUDED