#include <EngineSystem/Input/Input.h>

namespace INPUT {

ID Input::getId() const {
    return id;
}

void Input::setId(ID id_) {
    id = id_;
}

Input::Input(ID id_)
    : id(id_)
{
}

}
