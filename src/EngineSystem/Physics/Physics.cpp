#include <EngineSystem/Physics/Physics.h>

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

    float Rectangle::getX1() {
        return X1;
    }

    float Rectangle::getX2() {
        return X2;
    }

    float Rectangle::getY1() {
        return Y1;
    }

    float Rectangle::getY2() {
        return Y2;
    }


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
    
    LinearFunction findLinearFunction(Point& A, Point& B) {
        if (A.getX() == B.getX())
            return LinearFunction(1.0, 0.0, -1 * A.getX());

        float a = (A.getY() - B.getY()) / (A.getX() - B.getX());
        float c = B.getY() - a * B.getX();

        return LinearFunction(a, -1.0, c);
    }

    std::pair<Point, bool> linesIntersection(LinearFunction& f, LinearFunction& g) {
        float den = (f.getB() * g.getA() - g.getB() * f.getA());
        if (den == 0) return std::make_pair(Point(0.0, 0.0), false);

        float y = (g.getC() * f.getA() - f.getC() * g.getA()) / den;
        float x = (f.getC() * g.getB() - f.getB() * g.getC()) / den;

        return std::make_pair(Point(x, y), true);
    }

    float pointPointDistance(Point& A, Point& B) {
        return sqrt((B.getX() - A.getX()) * (B.getX() - A.getX()) + (B.getY() - A.getY()) * (B.getY() - A.getY()));
    }

    Point getClosestIntersectionPoint(LinearFunction& f, LinearFunction& g1, LinearFunction& g2, Point& A) {
        std::pair<Point, bool> P1 = linesIntersection(f, g1);
        std::pair<Point, bool> P2 = linesIntersection(f, g2);

        float D1 = pointPointDistance(A, P1.first);
        float D2 = pointPointDistance(A, P2.first);
        float minD;

        if (P1.second && P2.second) minD = std::min(D1, D2);
        else if (P1.second) minD = D1;
        else minD = D2;

        if (minD == D1) return P1.first;
        return P2.first;
    }
    
    glm::vec2 checkCollision(Rectangle& A, glm::vec2 velocity, Rectangle& B) {
        if (A.getX1() >= B.getX2() || A.getX2() <= B.getX1() ||
            A.getY1() >= B.getY2() || A.getY2() <= B.getY1())
            return glm::vec2(0.0, 0.0);

        glm::vec2 resultVector;

        if (velocity.x > 0 && velocity.y >= 0)
        {
            Point current = Point(A.getX2(), A.getY2());
            Point previous = Point(A.getX2() - velocity.x, A.getY2() - velocity.y);
            LinearFunction f = findLinearFunction(current, previous);
            LinearFunction g1(1.0, 0.0, -1 * B.getX1());
            LinearFunction g2(0.0, 1.0, -1 * B.getY1());

            Point closestPoint = getClosestIntersectionPoint(f, g1, g2, current);

            resultVector = glm::vec2(closestPoint.getX() - current.getX(), closestPoint.getY() - current.getY());
        }
        else if (velocity.x > 0 && velocity.y <= 0)
        {
            Point current = Point(A.getX2(), A.getY1());
            Point previous = Point(A.getX2() - velocity.x, A.getY1() - velocity.y);
            LinearFunction f = findLinearFunction(current, previous);
            LinearFunction g1(1.0, 0.0, -1 * B.getX1());
            LinearFunction g2(0.0, 1.0, -1 * B.getY2());

            Point closestPoint = getClosestIntersectionPoint(f, g1, g2, current);

            resultVector = glm::vec2(closestPoint.getX() - current.getX(), closestPoint.getY() - current.getY());
        }
        else if (velocity.x <= 0 && velocity.y > 0)
        {
            Point current = Point(A.getX1(), A.getY2());
            Point previous = Point(A.getX1() - velocity.x, A.getY2() - velocity.y);
            LinearFunction f = findLinearFunction(current, previous);
            LinearFunction g1(1.0, 0.0, -1 * B.getX2());
            LinearFunction g2(0.0, 1.0, -1 * B.getY1());

            Point closestPoint = getClosestIntersectionPoint(f, g1, g2, current);

            resultVector = glm::vec2(closestPoint.getX() - current.getX(), closestPoint.getY() - current.getY());
        }
        else if (velocity.x <= 0 && velocity.y < 0)
        {
            Point current = Point(A.getX1(), A.getY1());
            Point previous = Point(A.getX1() - velocity.x, A.getY1() - velocity.y);
            LinearFunction f = findLinearFunction(current, previous);
            LinearFunction g1(1.0, 0.0, -1 * B.getX2());
            LinearFunction g2(0.0, 1.0, -1 * B.getY1());

            Point closestPoint = getClosestIntersectionPoint(f, g1, g2, current);

            resultVector = glm::vec2(closestPoint.getX() - current.getX(), closestPoint.getY() - current.getY());
        }

        return resultVector;
    }
    
}