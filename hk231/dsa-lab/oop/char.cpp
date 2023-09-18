#include <iostream>
#include <math.h>

using namespace std;

class Character {
protected:
    int hp;
    int x;
    int y;
public:
    Character();
    Character(int hp, int x, int y);

    int getHp();
    void setHp(int hp);

    int getX();
    void setX(int x);
    
    int getY();
    void setY(int y);

    int getManhattanDistTo(Character* other);
};

Character::Character() {
    hp = x = y = 0;
}

Character::Character(int hp, int x, int y) {
    this->hp = hp;
    this->x = x;
    this->y = y;
}

int Character::getHp() {
    return hp;
}

void Character::setHp(int hp) {
    this->hp = hp;
}

int Character::getX() {
    return x;
}

void Character::setX(int x) {
    this->x = x;
}

int Character::getY() {
    return y;
}

void Character::setY(int y) {
    this->y = y;
}

int Character::getManhattanDistTo(Character* A) {
    return abs(x - A->getX()) + abs(y - A->getY());
}

int main() {
    Character ch1(100, 3, 6);
    cout << ch1.getHp() << " " << ch1.getX() << " " << ch1.getY();
}