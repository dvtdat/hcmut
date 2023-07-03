#include <iostream>
#include "stack.cpp"

using namespace std;

int main()
{
    MyStack<int> s;
    for (int i = 0; i < 1; ++i)
    {
        s.push(10 * i);
    }
    
    MyStack<int> t;
    t = move(s);

    t.push(10);
    t.push(10);
    t.push(10);
    t.push(10);

    cout << s.size() << '\n';
    cout << t.size() << '\n';
}