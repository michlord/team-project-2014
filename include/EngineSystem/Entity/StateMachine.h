#ifndef ENGINE_SYSTEM_ENTITY_STATE_MACHNIE_H_INCLUDED
#define ENGINE_SYSTEM_ENTITY_STATE_MACHNIE_H_INCLUDED

#include <EngineSystem/Log/Log.h>

#include "State.h"
#include "Message.h"

#include <memory>

namespace Entity {

template <typename entityT>
class StateMachine {
    public:
        typedef std::shared_ptr< State<entityT> > StatePtr;
    private:
        entityT*        owner;
        StatePtr currentState;
        StatePtr globalState;
        StatePtr oldState;
    public:
        StateMachine(entityT* owner_, State<entityT>* globalState_ = nullptr)
         : owner(owner_), currentState(nullptr), globalState(globalState_)
        {
        }

        void update() {
            if(globalState) {
                globalState->onUpdate(owner);
            }
            if(currentState) {
                currentState->onUpdate(owner);
            }
        }
        
        StatePtr changeState(State<entityT>* newState) {
            if(newState == nullptr) {
                Log::get().write(Log::System::Engine, "[State machine] Tried to use nullptr for the newState");
                return StatePtr();
            } else {
                oldState = currentState;
                currentState.reset(newState);
                if(oldState) {
                    oldState->onExit(owner);
                }
                currentState->onEnter(owner);
                return oldState;
            }
        }
        
        StatePtr getCurrentState() {
            return currentState;
        }
        
        bool handleMessage(const Message &msg) {
            if(globalState && globalState->onMessage(owner, msg)) {
                return true;
            }
            if(currentState && currentState->onMessage(owner, msg)) {
                return true;
            }
            return false;
        }
};

}

#endif // ENGINE_SYSTEM_ENTITY_STATE_MACHNIE_H_INCLUDED
