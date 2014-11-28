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

                AnimatedSprite* getSequence(const std::string& name_);
                const AnimatedSprite* getSequence(const std::string& name_) const;

            private:
                bool isNullWindowWarningPrinted;
                bool isNoSequenceWarningPrinted;

                bool isCurrentSet;
                std::string currentSequence;

                std::unordered_map<std::string, AnimatedSprite> spriteSequences;
                std::unordered_map<std::string, Control> sequenceControl;

        };

    }

}

#endif