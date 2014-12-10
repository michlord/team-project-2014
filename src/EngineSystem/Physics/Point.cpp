#include <EngineSystem/Physics/Point.h>

namespace Physics
{
    Point::Point() {
        x = 0.0;
        y = 0.0;
    }

    Point::Point(float x_, float y_) {
        x = x_;
        y = y_;
    }

    float Point::getX() {
        return x;
    }

    float Point::getY() {
        return y;
    }

}
