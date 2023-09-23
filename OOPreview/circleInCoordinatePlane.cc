#include <iostream>
#include <cstdio>
#include <math.h>

class Point
{
private:
    double x, y;

public:
    Point()
    {
        this->x = 0;
        this->y = 0;
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
        return this->x;
    }

    double getY() const
    {
        return this->y;
    }

    double distanceToPoint(const Point& pointA)
    {
        double sum = (pointA.x - this->x) * (pointA.x - this->x) + (pointA.y - this->y) * (pointA.y - this->y);
        double final = sqrt(sum);
        return final;
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
        this->radius = 0;
    }

    Circle(Point center, double radius)
    {
        this->center = center;
        this->radius = radius;
    }

    Circle(const Circle &circle)
    {
        this->center = circle.center;
        this->radius = circle.radius;
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
        return this->center;
    }

    double getRadius() const
    {
        return this->radius;
    }
    
    void printCircle()
    {
        printf("Center: {%.2f, %.2f} and Radius %.2f\n", this->center.getX(), this->center.getY(), this->radius);
    }
};

int main(int argc, char** argv) {
    int i = 0;
    {
        std::cout << "Case" << " " << ++i << std::endl;
        Circle A;
        A.printCircle();
    }
    {
        std::cout << "Case" << " " << ++i << std::endl;
        Point pointO(0, 2);
        Circle A = Circle(pointO, 20);
        A.printCircle();
    }
    {
        std::cout << "Case" << " " << ++i << std::endl;
        Point pointO(0, 2);
        Circle A = Circle(pointO, 20);
        Circle B = A;
        B.printCircle();
    }
    {
        std::cout << "Case" << " " << ++i << std::endl;
        Point pointO(0, 1);
        Circle A = Circle(pointO, 20);
        Circle B(A);
        B.printCircle();
    }
    return 0;
}