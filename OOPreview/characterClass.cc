#include <iostream>
#include <cstdio>
#include <math.h>

using namespace std;

class Character {
protected:
    int hp;
    int x;
    int y;
public:
    // Constructor: set the values of x and y and hp to 0
    Character();


    // Constructor: set the values of hp, x and y to each parameter
    Character(int hp, int x, int y);


    // Set and get hp
    int getHp();
    void setHp(int hp);


    // Set and get x
    int getX();
    void setX(int x);
    
    // Set and get y
    int getY();
    void setY(int y);


    // Get Manhattan distance to other character
    int getManhattanDistTo(Character* other);
};


Character::Character(): hp(0), x(0), y(0) {
}

Character::Character(int hp, int x, int y): hp(hp), x(x), y(y) {
}

int Character::getHp() {
    return this->hp;
}

void Character::setHp(int hp) {
    this->hp = hp;
}

int Character::getX() {
    return this->x;
}

void Character::setX(int x) {
    this->x = x;
}

int Character::getY() {
    return this->y;
}

void Character::setY(int y) {
    this->y = y;
}

int Character::getManhattanDistTo(Character* other) {
    int targetX = other->x;
    int targetY = other->y;
    return abs(this->x - targetX) + abs(this->y - targetY);
}

int main() {
    int i = 0;
    {
        std::cout << "Case" << " " << ++i << std::endl;
        Character ch1(100, 3, 6);
        cout << ch1.getHp() << " " << ch1.getX() << " " << ch1.getY();
        std::cout << endl;
    }
    {
        std::cout << "Case" << " " << ++i << std::endl;
        Character ch2;
        cout << ch2.getHp() << " " << ch2.getX() << " " << ch2.getY();
        std::cout << endl;
    }
    {
        std::cout << "Case" << " " << ++i << std::endl;
        Character* ch31 = new Character(100, 1, 2);
        Character* ch32 = new Character(100, -3, 4);
        cout << ch31->getManhattanDistTo(ch32);
        delete ch31;
        delete ch32;
        std::cout << endl;
    }
    {
        std::cout << "Case" << " " << ++i << std::endl;
        Character ch4;
        ch4.setX(4);
        cout << ch4.getX();
        std::cout << endl;
    }

    return 0;
}
