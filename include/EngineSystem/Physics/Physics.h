#ifndef ENGINE_SYSTEM_PHYSICS_PHYSICS_H_INCLUDED
#define ENGINE_SYSTEM_PHYSICS_PHYSICS_H_INCLUDED

#include <string>
#include <glm/glm.hpp>
#include <cmath>
#include "Rectangle.h"
#include "Point.h"
#include "Circle.h"
#include "LinearFunction.h"

namespace Physics
{
    LinearFunction findLinearFunction(Point& A, Point& B);
    std::pair<Point, bool> linesIntersection(LinearFunction& f, LinearFunction& g);
    float pointPointDistance(Point& A, Point& B);
    Point getClosestIntersectionPoint(LinearFunction& f, LinearFunction& g1, LinearFunction& g2, Point& P);
    glm::vec2 checkCollision(Rectangle& A, glm::vec2 velocity, Rectangle& B);
    bool checkCollision(Circle& A, Circle& B);
}

#endif