#include <exception>
#include <iostream>

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
        std::cout << "sum: " << sum << std::endl;
        double final = sqrt(sum);
        std::cout << "final: " << final << std::endl;
        double re = pow(final, 2);
        std::cout << "re: " << re << std::endl;
        return final;
    }
};

int main(int argc, char *argv[]) {
    {
        std::cout << "Case 1" << std::endl;
        Point A(2, 3);
        if (A.getX() != 2) throw new std::exception();
        if (A.getY() != 3) throw new std::exception();
    }
    //{
    //    std::cout << "Case 2" << std::endl;
    //    Point A(2, 3);
    //    Point B(1, 1);
    //    double val = pow(A.distanceToPoint(B), 2);
    //    std::cout << val << std::endl;
    //    if (val != 5) throw new std::exception();
    //}
    {
        std::cout << "Case 3" << std::endl;
        Point A;
        A.setX(2);
        A.setY(3);
        if (A.getX() != 2) throw new std::exception();
        if (A.getY() != 3) throw new std::exception();
    }
    {
        std::cout << "Case 4" << std::endl;
        Point A;
        A.setX(2);
        if (A.getX() != 2) throw new std::exception();
        if (A.getY() != 0) throw new std::exception();
    }
    //{
    //    std::cout << "Case 5" << std::endl;
    //    Point A(2, 3);
    //    Point B(0, 0);
    //    if (pow(A.distanceToPoint(B), 2) != 13) throw new std::exception();
    //}

    return 0;
}