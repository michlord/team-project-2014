#include <EngineSystem/Physics/LinearFunction.h>

namespace Physics
{
    LinearFunction::LinearFunction(float a_, float b_, float c_) {
        a = a_;
        b = b_;
        c = c_;
    }

    float LinearFunction::getA() {
        return a;
    }

    float LinearFunction::getB() {
        return b;
    }

    float LinearFunction::getC() {
        return c;
    }

}
