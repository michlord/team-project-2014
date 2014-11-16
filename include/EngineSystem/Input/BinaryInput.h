#ifndef ENGINE_SYSTEM_INPUT_BINARY_INPUT_H_INCLUDED
#define ENGINE_SYSTEM_INPUT_BINARY_INPUT_H_INCLUDED

#include "Input.h"

namespace INPUT {

class BinaryInput : public Input {
    private:
        bool pressed; //or released
    public:
        bool isPressed() const;
        void setPressed(bool pressed_);
        BinaryInput(ID id_, bool pressed_);
};

}

#endif // ENGINE_SYSTEM_INPUT_BINARY_INPUT_H_INCLUDED
