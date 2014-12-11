#include <EngineSystem/Physics/LinearFunction.h>

namespace Physics
{
    LinearFunction::LinearFunction(float a_, float b_, float c_) {
        a = a_;
        b = b_;
        c = c_;
    }

    float LinearFunction::getA() const {
        return a;
    }

    float LinearFunction::getB() const {
        return b;
    }

    float LinearFunction::getC() const {
        return c;
    }

}
