#include <EngineSystem/Input/Context.h>
#include <EngineSystem/Input/Input.h>
#include <EngineSystem/Input/BinaryInput.h>
#include <EngineSystem/Input/AxisInput.h>
#include <utility>
#include <cmath>

namespace INPUT {

Context::Context(bool active_)
    : active(active_)
{
}

bool Context::isActive() {
    return active;
}

void Context::setActive(bool active_) {
    active = active_;
}

void Context::handleAction(const Input &input, const ActionCallback &callback) {
    if(const BinaryInput *p = dynamic_cast<const BinaryInput*>(&input)) {
        if(p->isPressed()) {
            callback();
        }
    } else {
        callback();
    }
}

void Context::handleState(const Input &input, const StateCallback &callback) {
    if(const BinaryInput *p = dynamic_cast<const BinaryInput*>(&input)) {
        callback(p->isPressed());
    } else if (const AxisInput *p = dynamic_cast<const AxisInput*>(&input)) {
        callback(fabs(p->getOffset()) > 0.3);
    }
}

void Context::handleRange(const Input &input, const RangeCallback &callback) {
    if(const BinaryInput *p = dynamic_cast<const BinaryInput*>(&input)) {
        if(p->isPressed()) {
            callback(1.0f);
        }
    } else if (const AxisInput *p = dynamic_cast<const AxisInput*>(&input)) {
        callback(p->getOffset());
    }
}

bool Context::handleInput(const Input &input) {
    auto p = inputMap.find(input.getId());
    if (p != inputMap.end()) {
        std::string name = p->second;
        auto a = actions.find(name);
        auto b = states.find(name);
        auto c = ranges.find(name);
        
        if(a != actions.end()) {
            for(auto it = a->second.begin();
                it != a->second.end();
                ++it) 
            {
                handleAction(input, *it);
            }
            return true;
        }
        if (b != states.end()) {
            for(auto it = b->second.begin();
                it != b->second.end();
                ++it) 
            {
                handleState(input, *it);
            }
            return true;
        }
        if (c != ranges.end()) {
            for(auto it = c->second.begin();
                it != c->second.end();
                ++it) 
            {
                handleRange(input, *it);
            }
            return true;
        }
    }
    return false;
}

bool Context::addBinding(const char *name, ID inputId) {
    auto p = inputMap.insert(std::make_pair(inputId, name));
    return p.second;
}

void Context::addAction(const char *name, ActionCallback handler) {
    actions[name].push_back(handler);
}

void Context::addState(const char *name, StateCallback handler) {
    states[name].push_back(handler);
}

void Context::addRange(const char *name, RangeCallback handler) {
    ranges[name].push_back(handler);
}

}
