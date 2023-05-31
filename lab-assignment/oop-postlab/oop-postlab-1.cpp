#include <iostream>
#include <string>

using namespace std;

class Coordinate
{
private:
    int x;
    int y;
public:
    Coordinate(int x, int y): x(x), y(y) {};
    ~Coordinate() {};

    void setX(int xN);
    void setY(int yN);
    int getX();
    int getY();
    int distanceTo(Coordinate&);
};

void Coordinate::setX(int xN)
{
    x = xN;
}

void Coordinate::setY(int yN)
{
    y = yN;
}

int Coordinate::getX()
{
    return x;
}

int Coordinate::getY()
{
    return y;
}

int Coordinate::distanceTo(Coordinate& a)
{
    return abs(x - a.getX()) + abs(y - a.getY());
}

int main()
{
    Coordinate a(0, 0), b(2, 3);

    cout << a.distanceTo(b) << '\n';
}