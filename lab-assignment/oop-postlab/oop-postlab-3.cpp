#include <iostream>

using namespace std;

template<typename T>
class Array
{
private:
    int size;
    T* p;
public:
    Array(int size, T initValue);
    ~Array();
    void setAt(int idx, const T & value);
    T getAt(int idx);
    void print();
};

template<typename T>
Array<T>::Array(int size, T initValue) : size(size)
{
    p = new T[size];
    for (int i = 0; i < size; ++i) p[i] = initValue;
}

template<typename T>
Array<T>::~Array()
{
    delete[] p;
}

template<typename T>
void Array<T>::setAt(int idx, const T& value)
{
    if (idx < 0 && idx >= size) throw -1;
    p[idx] = value;
}

template<typename T>
T Array<T>::getAt(int idx)
{
    if (idx < 0 && idx >= size) throw -1;
    return p[idx];
}

template<typename T>
void Array<T>::print()
{
    for (int i = 0; i < this->size; ++i)
    {
        cout << (i > 0 ? " " : "") << this->p[i];
    }
    cout << '\n';
}


int main()
{
    Array<int> arr(10, 0);
    arr.print();
    for (int i = 0; i < 10; ++i) arr.setAt(i, i);
    arr.print();

    Array<string> arrStr(10, "hahaha");
    arrStr.print();
    arrStr.setAt(1, "hohoho");
    arrStr.setAt(4, "hehehe");
    arrStr.setAt(9, "huhuhu");
    arrStr.print();
}