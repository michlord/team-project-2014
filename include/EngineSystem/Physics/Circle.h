#ifndef ENGINE_SYSTEM_PHYSICS_CIRCLE_H_INCLUDED
#define ENGINE_SYSTEM_PHYSICS_CIRCLE_H_INCLUDED

#include "Point.h"

namespace Physics
{
    class Circle
    {
    public:
        Circle();
        Circle(Point center_, float radius_);
        Point getCenter();
        float getRadius();

    private:
        Point center;
        float radius;
    };
}

#endif
