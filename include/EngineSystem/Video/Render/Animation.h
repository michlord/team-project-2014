#ifndef ENGINE_SYSTEM_VIDEO_RENDER_ANIMATION_H_INCLUDED
#define ENGINE_SYSTEM_VIDEO_RENDER_ANIMATION_H_INCLUDED

#include <EngineSystem/Video/Render/AnimatedSprite.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <unordered_map>
#include <functional>

namespace Video {

    namespace Render {

        class Animation : public sf::Drawable {
            public:
                struct Control {
                    Control() : nextSequence("") { }

                    std::function<void()> onDone;
                    std::string nextSequence;
                };

            public:
                Animation();
                ~Animation();

                void update(const sf::Time& timeElapsed_);
                void draw(sf::RenderWindow* windowHandle_) const;
                void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;

                void addSequence(const std::string& name_, const AnimatedSprite& spriteSequence_, bool repeat_);
                void addSequence(const std::string& name_, const AnimatedSprite& spriteSequence_, const std::string& next_);
                void addSequence(const std::string& name_, const AnimatedSprite& spriteSequence_, const char* next_);
                void addSequence(const std::string& name_, const AnimatedSprite& spriteSequence_, const std::function<void()> onDone_);

                void setCurrentSequence(const std::string& name_);

                void setRotation(float angle_);
                void setPosition(const sf::Vector2f& position_);
                void setSize(const sf::Vector2u& size_);
                void setColorMask(const sf::Color& mask_);

                void rotate(float angle_);
                void move(const sf::Vector2f& offset_);
                void scale(const sf::Vector2f& scale_);

                AnimatedSprite* getSequence(const std::string& name_);
                const AnimatedSprite* getSequence(const std::string& name_) const;
                
                float getRotation() const;
                const sf::Vector2f& getPosition() const;
                const sf::Vector2u& getSize() const;
                const sf::Color& getColorMask() const;

                void repositionAll();
                void resizeAll();
                void rerotateAll();
                void recolorAll();

            private:
                bool isNullWindowWarningPrinted;
                bool isNoSequenceWarningPrinted;

                bool isCurrentSet;
                std::string currentSequence;

                float rotation;
                sf::Color colorMask;
                sf::Vector2u size;
                sf::Vector2f position;

                std::unordered_map<std::string, AnimatedSprite> spriteSequences;
                std::unordered_map<std::string, Control> sequenceControl;

        };

    }

}

#endif