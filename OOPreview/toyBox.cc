#include <functional>
#include <iostream>
#include <cstdio>
#include <math.h>
#include "../Utils/utils.h"

using namespace std;

enum Color
{
    red,
    green,
    blue
};
enum Size
{
    small,
    medium,
    big
};

class Toy
{
protected:
    double price;

public:
    Toy(double price)
    {
        this->price = price;
    }

    virtual void printType() = 0;
    friend class ToyBox;
};

class CarToy : public Toy
{
private:
    Color color;

public:
    CarToy(double price, Color color) : Toy(price), color(color)
    {
    }

    void printType()
    {
        cout << "This is a car toy\n";
    }

    friend class ToyBox;
};

class PuzzleToy : public Toy
{
private:
    Size size;

public:
    PuzzleToy(double price, Size size) : Toy(price), size(size)
    {
    }

    void printType()
    {
        cout << "This is a puzzle toy\n";
    }

    friend class ToyBox;
};

class ToyBox
{
private:
    Toy* toyBox[5];
    int numberOfItems;

public:
    ToyBox(): numberOfItems(0)
    {
        for (int i = 0; i < 5; i++) {
            this->toyBox[i] = nullptr;
        }
    }
    
    int addItem(const CarToy& carToy)
    {
        if (this->numberOfItems == 5) {
            return -1;
        }
        this->toyBox[this->numberOfItems++] = (Toy*)(&carToy);        
        return this->numberOfItems;
    }
    
    int addItem(const PuzzleToy& puzzleToy)
    {
        if (this->numberOfItems == 5) {
            return -1;
        }
        this->toyBox[this->numberOfItems++] = (Toy*)(&puzzleToy);
        return this->numberOfItems;
    }
    
    void printBox()
    {
        for (int i = 0; i < numberOfItems; i++)
            toyBox[i]->printType();
    }
};

int main() {
    utils::assert([]() {
        CarToy car(20000,red);
        PuzzleToy puzzle(30000,small);
        car.printType();
        puzzle.printType();
        return 0;
    });
    utils::assert([]() {
        CarToy car(20000,red);
        PuzzleToy puzzle(30000,small);

        ToyBox box;
        box.addItem(car);
        box.addItem(puzzle);
        box.printBox();
        return 0;
    });
    utils::assert([]() {
        CarToy car(20000,red);
        PuzzleToy puzzle(30000,small);

        ToyBox box;
        cout << box.addItem(car)<<endl;
        cout << box.addItem(puzzle)<<endl;
        cout << box.addItem(car)<<endl;
        cout << box.addItem(puzzle)<<endl;
        box.printBox();
        return 0;
    });
    utils::assert([]() {
        CarToy car(20000,red);
        PuzzleToy puzzle(30000,small);

        ToyBox box;
        cout << box.addItem(car)<<endl;
        cout << box.addItem(car)<<endl;
        box.printBox();
        return 0;

    });

    utils::assert([]() {
        CarToy car(20000,red);
        PuzzleToy puzzle(30000,small);

        ToyBox box;
        cout << box.addItem(car)<<endl;
        cout << box.addItem(puzzle)<<endl;
        cout << box.addItem(car)<<endl;
        cout << box.addItem(puzzle)<<endl;
        cout << box.addItem(car)<<endl;
        cout << box.addItem(puzzle)<<endl;
        box.printBox();
        return 0;
    });
    return 0;
}