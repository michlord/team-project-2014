#ifndef ENGINE_SYSTEM_ENTITY_STATE_MACHNIE_H_INCLUDED
#define ENGINE_SYSTEM_ENTITY_STATE_MACHNIE_H_INCLUDED

#include "State.h"
#include "Message.h"

namespace Entity {

template <typename entityT>
class StateMachine {
    private:
        entityT*        owner;
        State<entityT>* currentState;
    public:
        StateMachine(entityT* owner_)
         : owner(owner_), currentState(nullptr)
        {
        }
    
        void update() {
            if(currentState) {
                currentState->onUpdate(owner);
            }
        }
        
        State<entityT>* changeState(State<entityT>* newState) {
            State<entityT>* oldState = currentState;
            // Log an attempt to use nullptr for the newState. (When the logs are ready)
            if(newState) {
                if(oldState) {
                    oldState->onExit(owner);
                }
                currentState = newState;
                newState->onEnter(owner);
            }
            return oldState;
        }
        
        State<entityT>* getCurrentState() {
            return currentState;
        }
        
        bool handleMessage(const Message &msg) {
            if(currentState && currentState->onMessage(owner, msg)) {
                return true;
            }
            return false;
        }
};

}

#endif // ENGINE_SYSTEM_ENTITY_STATE_MACHNIE_H_INCLUDED
