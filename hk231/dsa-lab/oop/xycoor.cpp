#include <iostream>
#include <math.h>

using namespace std;

class Point
{
private:
    double x, y;

public:
    Point()
    {
        x = y = 0.0;
    }

    Point(double x, double y)
    {
        this->x = x;
        this->y = y;
    }

    void setX(double x)
    {
        this->x = x;
    }

    void setY(double y)
    {
        this->y = y;
    }

    double getX() const
    {
        return x;
    }

    double getY() const
    {
        return y;
    }

    double distanceToPoint(const Point& A)
    {
        return 1.0 * sqrt((x - A.getX()) * (x - A.getX()) + (y - A.getY()) * (y - A.getY()));
    }
};

class Circle
{
private:
    Point center;
    double radius;

public:
    Circle()
    {
        this->center = Point(0, 0);
        this->radius = 0;
    }

    Circle(Point center, double radius)
    {
        this->center = center;
        this->radius = radius;
    }

    Circle(const Circle &circle)
    {
        this->center = circle.getCenter();
        this->radius = circle.getRadius();
    }
    
    void setCenter(Point point)
    {
        this->center = point;
    }

    void setRadius(double radius)
    {
        this->radius = radius;
    }

    Point getCenter() const
    {
        return center;
    }

    double getRadius() const
    {
        return radius;
    }
    
    void printCircle()
    {
        printf("Center: {%.2f, %.2f} and Radius %.2f\n", this->center.getX(), this->center.getY(), this->radius);
    }
};

int main() {
    Circle A(Point(1, 2), 10);
    A.printCircle();
}