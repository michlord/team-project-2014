#ifndef ENGINE_SYSTEM_PHYSICS_PHYSICS_H_INCLUDED
#define ENGINE_SYSTEM_PHYSICS_PHYSICS_H_INCLUDED

#include <string>
#include <glm/glm.hpp>
#include <cmath>
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


    class Point
    {
    public:
        Point();
        Point(float x_, float y_);

        float getX();
        float getY();

    private:
        float x;
        float y;
    };


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


    class LinearFunction
    {
    public:
        LinearFunction(float a_, float b_, float c_);

        float getA();
        float getB();
        float getC();

    private:
        // ax + by + c = 0
        float a;
        float b;
        float c;
    };
    
    LinearFunction findLinearFunction(Point& A, Point& B);
    std::pair<Point, bool> linesIntersection(LinearFunction& f, LinearFunction& g);
    float pointPointDistance(Point& A, Point& B);
    Point getClosestIntersectionPoint(LinearFunction& f, LinearFunction& g1, LinearFunction& g2, Point& P);
    glm::vec2 checkCollision(Rectangle& A, glm::vec2 velocity, Rectangle& B);
}

#endif