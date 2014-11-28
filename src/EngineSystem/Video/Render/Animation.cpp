#include <EngineSystem/Video/Render/Animation.h>
#include <EngineSystem/Log/Log.h>

#include <iostream>

namespace Video {

    namespace Render {

        Animation::Animation() {
            currentSequence = "";
            isCurrentSet = false;
            isNullWindowWarningPrinted = false;
            isNoSequenceWarningPrinted = false;
        }

        Animation::~Animation() {

        }

        void Animation::update(const sf::Time& timeElapsed_) {
            if(isCurrentSet) {
                getSequence(currentSequence)->update(timeElapsed_);

                if(getSequence(currentSequence)->isFinished()) {
                    if(sequenceControl[currentSequence].nextSequence != "") {
                        getSequence(currentSequence)->resetCurrentFrame();
                        getSequence(currentSequence)->resetFinished();
                        currentSequence = sequenceControl[currentSequence].nextSequence;

                    } else if(sequenceControl[currentSequence].onDone) {
                        getSequence(currentSequence)->resetCurrentFrame();
                        getSequence(currentSequence)->resetFinished();
                        sequenceControl[currentSequence].onDone();
                    }
                }
            }
        }

        void Animation::draw(sf::RenderWindow* windowHandle_) const {
            if(windowHandle_) {
                draw(*windowHandle_);
            } else if(isNullWindowWarningPrinted == false) {
                const_cast<Animation*>(this)->isNullWindowWarningPrinted = true;
                Log::get().write(Log::System::Engine, "[Animation] Attempt to draw on 'null' window!");
            }
        }

        void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const {
            if(isCurrentSet) {
                getSequence(currentSequence)->draw(target, states);
            } else if(isNoSequenceWarningPrinted == false) {
                const_cast<Animation*>(this)->isNoSequenceWarningPrinted = true;
                Log::get().write(Log::System::Engine, "[Animation] Attempt to draw without current sequence: '%s'", currentSequence.c_str());
            }
        }

        void Animation::addSequence(const std::string& name_, const AnimatedSprite& spriteSequence_, bool repeat_) {
            spriteSequences.insert(std::make_pair(name_, spriteSequence_));
            getSequence(name_)->setRepeat(repeat_);
            
            Control control;
            sequenceControl.insert(std::make_pair(name_, control));
        }

        void Animation::addSequence(const std::string& name_, const AnimatedSprite& spriteSequence_, const std::string& next_) {
            spriteSequences.insert(std::make_pair(name_, spriteSequence_));

            Control control;
            sequenceControl.insert(std::make_pair(name_, control));

            sequenceControl[name_].nextSequence = next_;
        }
        
        void Animation::addSequence(const std::string& name_, const AnimatedSprite& spriteSequence_, const char* next_) {
            addSequence(name_, spriteSequence_, std::string(next_));
        }

        void Animation::addSequence(const std::string& name_, const AnimatedSprite& spriteSequence_, const std::function<void()> onDone_) {
            spriteSequences.insert(std::make_pair(name_, spriteSequence_));
            
            Control control;
            sequenceControl.insert(std::make_pair(name_, control));
            sequenceControl[name_].onDone = onDone_;
        }
        
        void Animation::setCurrentSequence(const std::string& name_) {
            if(isCurrentSet)
                spriteSequences[name_].resetCurrentFrame();
            
            currentSequence = name_;

            try {
                spriteSequences.at(currentSequence).resetCurrentFrame();
                isCurrentSet = true;
            } catch(const std::out_of_range& exception)  {
                Log::get().write(Log::System::Engine, "[Animation] Current sequence is set as non-existing: '%s'", name_.c_str());
                Log::get().write(Log::System::Engine, "[Animation] Out of range exception: '%s'", exception.what());
                isCurrentSet = false;
            }
        }

        AnimatedSprite* Animation::getSequence(const std::string& name_) {
            AnimatedSprite* result = nullptr;

            try {
                result = &spriteSequences.at(name_);

            } catch(const std::out_of_range& exception) {
                Log::get().write(Log::System::Engine, "[Animation] Request for sequence which doesn't exists: '%s'", name_.c_str());
                Log::get().write(Log::System::Engine, "[Animation] Out of range exception: '%s'", exception.what());
                result = nullptr;
            }

            return result;
        }

        const AnimatedSprite* Animation::getSequence(const std::string& name_) const {
            try {
                const AnimatedSprite* result = &spriteSequences.at(name_);
                return result;

            } catch(const std::out_of_range& exception) {
                Log::get().write(Log::System::Engine, "[Animation] Request for sequence which doesn't exists: '%s'", name_.c_str());
                Log::get().write(Log::System::Engine, "[Animation] Out of range exception: '%s'", exception.what());
                return nullptr;
            }
        }

    }

}