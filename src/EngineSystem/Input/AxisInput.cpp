#include <EngineSystem/Input/AxisInput.h>

namespace INPUT {

float AxisInput::getOffset() const {
    return offset;
}

void AxisInput::setOffset(float offset_) {
    offset = offset_;
}

AxisInput::AxisInput(ID id_, float offset_)
    : Input(id_), offset(offset_)
{
}

}
