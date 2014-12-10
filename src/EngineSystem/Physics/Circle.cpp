#include <EngineSystem/Physics/Circle.h>

namespace Physics
{
    Circle::Circle() {
        radius = 0.0;
    }

    Circle::Circle(Point center_, float radius_) {
        center = center_;
        radius = radius_;
    }

    Point Circle::getCenter() {
        return center;
    }

}
