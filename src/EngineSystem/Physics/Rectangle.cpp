#include <EngineSystem/Physics/Rectangle.h>

namespace Physics
{
    Rectangle::Rectangle() {
        X1 = 0.0;
        X2 = 0.0;
        Y1 = 0.0;
        Y2 = 0.0;
    }

    Rectangle::Rectangle(float x1_, float x2_, float y1_, float y2_) {
        if (x1_ > x2_) std::swap(x1_, x2_);
        if (y1_ > y2_) std::swap(y1_, y2_);

        X1 = x1_;
        X2 = x2_;
        Y1 = y1_;
        Y2 = y2_;
    }

    float Rectangle::getX1() const {
        return X1;
    }

    float Rectangle::getX2() const {
        return X2;
    }

    float Rectangle::getY1() const {
        return Y1;
    }

    float Rectangle::getY2() const {
        return Y2;
    }

}
