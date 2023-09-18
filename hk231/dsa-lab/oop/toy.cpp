#include <iostream>

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
    CarToy(double price, Color color) : Toy(price)
    {
        this->color = color;
    }

    CarToy(const CarToy &other) : Toy(other.price)
    {
        this->color = other.color;
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
    PuzzleToy(double price, Size size) : Toy(price)
    {
        this->size = size;
    }

    PuzzleToy(const PuzzleToy &other) : Toy(other.price)
    {
        this->size = other.size;
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
    ToyBox()
    {
        numberOfItems = 0;
        for (int i = 0; i < 5; ++i) toyBox[i] = nullptr;
    }
    
    int addItem(const CarToy& carToy)
    {
        if (numberOfItems >= 5) return -1;
        toyBox[numberOfItems++] = new CarToy(carToy);
        return numberOfItems;
    }
    
    int addItem(const PuzzleToy& puzzleToy)
    {
        if (numberOfItems >= 5) return -1;
        toyBox[numberOfItems++] = new PuzzleToy(puzzleToy);
        return numberOfItems;
    }
    
    void printBox()
    {
        for (int i = 0; i < numberOfItems; i++) toyBox[i]->printType();
    }
};

int main() {
    CarToy car(20000, red);
    PuzzleToy puzzle(30000, small);
    car.printType();
    puzzle.printType();
}