#include <iostream>

using namespace std;

class A
{
public:
    static int staticCnt;
    int cnt;

    A() { cnt++; }
    ~A() {}
};

class
{
public:
    int x;
    int y;
} a;

int A::staticCnt = 0;

int main()
{
    a.x = 10;
    cout << a.x;
}