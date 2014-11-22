#include <EngineSystem/Input/BinaryInput.h>

namespace Input {

bool BinaryInput::isPressed() const {
    return pressed;
}

void BinaryInput::setPressed(bool pressed_) {
    pressed = pressed_;
}

BinaryInput::BinaryInput(ID id_, bool pressed_)
    : Input(id_), pressed(pressed_)
{
}

}
