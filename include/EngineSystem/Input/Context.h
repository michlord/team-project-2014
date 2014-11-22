#ifndef ENGINE_SYSTEM_INPUT_CONTEXT_H_INCLUDED
#define ENGINE_SYSTEM_INPUT_CONTEXT_H_INCLUDED

#include <functional>
#include <map>
#include <string>
#include <vector>

#include "Input.h"

namespace Input {

class Context {
    public:
        typedef std::function< void() >      ActionCallback;
        typedef std::function< void(bool) >  StateCallback;
        typedef std::function< void(float) > RangeCallback;
    
    private:
        typedef std::map< ID, std::string >  InputBinding;
        
        typedef std::map< std::string, std::vector<ActionCallback> > ActionHandlerBinding;
        typedef std::map< std::string, std::vector<StateCallback> >  StateHandlerBinding;
        typedef std::map< std::string, std::vector<RangeCallback> >  RangeHandlerBinding;
        
        InputBinding         inputMap;
        ActionHandlerBinding actions;
        StateHandlerBinding  states;
        RangeHandlerBinding  ranges;
        
        bool active;
        
        void handleAction(const Input &input, const ActionCallback &callback);
        void handleState(const Input &input, const StateCallback &callback);
        void handleRange(const Input &input, const RangeCallback &callback);
        
    public:
        explicit Context(bool active_);
        
        bool isActive();
        void setActive(bool active_);
    
        bool handleInput(const Input &input);
        bool addBinding(const char *name, ID inputId);
        void addAction(const char *name, ActionCallback handler);
        void addState(const char *name, StateCallback handler);
        void addRange(const char *name, RangeCallback handler);
};

}

#endif // ENGINE_SYSTEM_INPUT_CONTEXT_H_INCLUDED
