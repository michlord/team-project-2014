#include <EngineSystem/Physics/Physics.h>

namespace Physics
{
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

    float pointPointDistance(const Point& A, const Point& B) {
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

        // NE
        if (velocity.x > 0 && velocity.y > 0)
        {
            Point current = Point(A.getX2(), A.getY2());
            Point previous = Point(A.getX2() - velocity.x, A.getY2() - velocity.y);
            LinearFunction f = findLinearFunction(current, previous);
            LinearFunction g1(1.0, 0.0, -1 * B.getX1());
            LinearFunction g2(0.0, 1.0, -1 * B.getY1());

            Point closestPoint = getClosestIntersectionPoint(f, g1, g2, current);

            resultVector = glm::vec2(closestPoint.getX() - current.getX(), closestPoint.getY() - current.getY());
        }// SE
        else if (velocity.x > 0 && velocity.y < 0)
        {
            Point current = Point(A.getX2(), A.getY1());
            Point previous = Point(A.getX2() - velocity.x, A.getY1() - velocity.y);
            LinearFunction f = findLinearFunction(current, previous);
            LinearFunction g1(1.0, 0.0, -1 * B.getX1());
            LinearFunction g2(0.0, 1.0, -1 * B.getY2());

            Point closestPoint = getClosestIntersectionPoint(f, g1, g2, current);

            resultVector = glm::vec2(closestPoint.getX() - current.getX(), closestPoint.getY() - current.getY());
        }// NW
        else if (velocity.x < 0 && velocity.y > 0)
        {
            Point current = Point(A.getX1(), A.getY2());
            Point previous = Point(A.getX1() - velocity.x, A.getY2() - velocity.y);
            LinearFunction f = findLinearFunction(current, previous);
            LinearFunction g1(1.0, 0.0, -1 * B.getX2());
            LinearFunction g2(0.0, 1.0, -1 * B.getY1());

            Point closestPoint = getClosestIntersectionPoint(f, g1, g2, current);

            resultVector = glm::vec2(closestPoint.getX() - current.getX(), closestPoint.getY() - current.getY());
        }// SW
        else if (velocity.x < 0 && velocity.y < 0)
        {
            Point current = Point(A.getX1(), A.getY1());
            Point previous = Point(A.getX1() - velocity.x, A.getY1() - velocity.y);
            LinearFunction f = findLinearFunction(current, previous);
            LinearFunction g1(1.0, 0.0, -1 * B.getX2());
            LinearFunction g2(0.0, 1.0, -1 * B.getY1());

            Point closestPoint = getClosestIntersectionPoint(f, g1, g2, current);

            resultVector = glm::vec2(closestPoint.getX() - current.getX(), closestPoint.getY() - current.getY());
        }// E
        else if (velocity.x > 0 && velocity.y == 0)
        {
            Point current = Point(A.getX2(), A.getY1());
            Point previous = Point(A.getX2() - velocity.x, A.getY1() - velocity.y);
            LinearFunction f = findLinearFunction(current, previous);
            LinearFunction g1(1.0, 0.0, -1 * B.getX1());
            LinearFunction g2(0.0, 1.0, -1 * B.getY2());

            Point closestPoint = getClosestIntersectionPoint(f, g1, g2, current);

            resultVector = glm::vec2(closestPoint.getX() - current.getX(), closestPoint.getY() - current.getY());
        }// W
        else if (velocity.x < 0 && velocity.y == 0)
        {
            Point current = Point(A.getX1(), A.getY1());
            Point previous = Point(A.getX1() - velocity.x, A.getY1() - velocity.y);
            LinearFunction f = findLinearFunction(current, previous);
            LinearFunction g1(1.0, 0.0, -1 * B.getX2());
            LinearFunction g2(0.0, 1.0, -1 * B.getY2());

            Point closestPoint = getClosestIntersectionPoint(f, g1, g2, current);

            resultVector = glm::vec2(closestPoint.getX() - current.getX(), closestPoint.getY() - current.getY());
        }// N
        else if (velocity.x == 0 && velocity.y > 0)
        {
            Point current = Point(A.getX1(), A.getY2());
            Point previous = Point(A.getX1() - velocity.x, A.getY2() - velocity.y);
            LinearFunction f = findLinearFunction(current, previous);
            LinearFunction g1(1.0, 0.0, -1 * B.getX1());
            LinearFunction g2(0.0, 1.0, -1 * B.getY1());

            Point closestPoint = getClosestIntersectionPoint(f, g1, g2, current);

            resultVector = glm::vec2(closestPoint.getX() - current.getX(), closestPoint.getY() - current.getY());
        }// S 
        else if (velocity.x == 0 && velocity.y < 0)
        {
            Point current = Point(A.getX1(), A.getY1());
            Point previous = Point(A.getX1() - velocity.x, A.getY1() - velocity.y);
            LinearFunction f = findLinearFunction(current, previous);
            LinearFunction g1(1.0, 0.0, -1 * B.getX2());
            LinearFunction g2(0.0, 1.0, -1 * B.getY2());

            Point closestPoint = getClosestIntersectionPoint(f, g1, g2, current);

            resultVector = glm::vec2(closestPoint.getX() - current.getX(), closestPoint.getY() - current.getY());
        }

        return resultVector;
    }
    

    
    bool checkCollision(Circle& A, Circle& B)
    {
        if (pointPointDistance(A.getCenter(), B.getCenter()) < A.getRadius() + B.getRadius())
            return true;

        return false;
    }


    sf::Vector2f checkCollision(sf::Vector2f point, sf::FloatRect rect, sf::Vector2f direction) {
        if (point.x >= rect.left + rect.width || point.x <= rect.left ||
            point.y >= rect.top || point.y <= rect.top - rect.height)
            return sf::Vector2f(0.0, 0.0);

        sf::Vector2f resultVector;

        if (direction.x > 0 && direction.y >= 0)
        {
            Point current = Point(point.x, point.y);
            Point previous = Point(point.x - direction.x, point.y - direction.y);
            LinearFunction f = findLinearFunction(current, previous);
            LinearFunction g1(1.0, 0.0, -1 * rect.left);
            LinearFunction g2(0.0, 1.0, -1 * rect.top - rect.height);

            Point closestPoint = getClosestIntersectionPoint(f, g1, g2, current);

            resultVector = sf::Vector2f(closestPoint.getX() - current.getX(), closestPoint.getY() - current.getY());
        }
        else if (direction.x > 0 && direction.y <= 0)
        {
            Point current = Point(point.x, point.y);
            Point previous = Point(point.x - direction.x, point.y - direction.y);
            LinearFunction f = findLinearFunction(current, previous);
            LinearFunction g1(1.0, 0.0, -1 * rect.left);
            LinearFunction g2(0.0, 1.0, -1 * rect.top);

            Point closestPoint = getClosestIntersectionPoint(f, g1, g2, current);

            resultVector = sf::Vector2f(closestPoint.getX() - current.getX(), closestPoint.getY() - current.getY());
        }
        else if (direction.x <= 0 && direction.y > 0)
        {
            Point current = Point(point.x, point.y);
            Point previous = Point(point.x - direction.x, point.y - direction.y);
            LinearFunction f = findLinearFunction(current, previous);
            LinearFunction g1(1.0, 0.0, -1 * rect.left + rect.width);
            LinearFunction g2(0.0, 1.0, -1 * rect.top - rect.height);

            Point closestPoint = getClosestIntersectionPoint(f, g1, g2, current);

            resultVector = sf::Vector2f(closestPoint.getX() - current.getX(), closestPoint.getY() - current.getY());
        }
        else if (direction.x <= 0 && direction.y < 0)
        {
            Point current = Point(point.x, point.y);
            Point previous = Point(point.x - direction.x, point.y - direction.y);
            LinearFunction f = findLinearFunction(current, previous);
            LinearFunction g1(1.0, 0.0, -1 * rect.left + rect.width);
            LinearFunction g2(0.0, 1.0, -1 * rect.top);

            Point closestPoint = getClosestIntersectionPoint(f, g1, g2, current);

            resultVector = sf::Vector2f(closestPoint.getX() - current.getX(), closestPoint.getY() - current.getY());
        }

        return resultVector;
    }



    sf::Vector2f checkCollision(sf::FloatRect rectA, sf::Vector2f direction, sf::FloatRect rectB) {
        Rectangle A(rectA.left, rectA.left + rectA.width, rectA.top - rectA.height, rectA.top);
        Rectangle B(rectB.left, rectB.left + rectB.width, rectB.top - rectB.height, rectB.top);
        glm::vec2 dir(direction.x, direction.y);

        glm::vec2 res = checkCollision(A, dir, B);
        
        return sf::Vector2f(res.x, res.y);
    }


}
