#ifndef ENGINE_SYSTEM_PHYSICS_POINT_H_INCLUDED
#define ENGINE_SYSTEM_PHYSICS_POINT_H_INCLUDED

namespace Physics
{
    class Point
    {
    public:
        Point();
        Point(float x_, float y_);

        float getX() const;
        float getY() const;

    private:
        float x;
        float y;
    };
}

#endif
