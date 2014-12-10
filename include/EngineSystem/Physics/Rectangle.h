#ifndef ENGINE_SYSTEM_PHYSICS_RECTANGLE_H_INCLUDED
#define ENGINE_SYSTEM_PHYSICS_RECTANGLE_H_INCLUDED

#include <algorithm>

namespace Physics
{
    class Rectangle
    {
    public:
        Rectangle();
        Rectangle(float x1_, float x2_, float y1_, float y2_);

        float getX1();
        float getX2();
        float getY1();
        float getY2();

    private:
        float X1, X2;
        float Y1, Y2;
    };
}

#endif
