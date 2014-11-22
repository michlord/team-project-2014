#ifndef ENGINE_SYSTEM_INPUT_AXIS_INPUT_H_INCLUDED
#define ENGINE_SYSTEM_INPUT_AXIS_INPUT_H_INCLUDED

#include "Input.h"

namespace Input {

class AxisInput : public Input {
    private:
        float offset;
    public:
        float getOffset() const;
        void  setOffset(float offset_);
        AxisInput(ID id_, float offset_);
};


}

#endif // ENGINE_SYSTEM_INPUT_AXIS_INPUT_H_INCLUDED
