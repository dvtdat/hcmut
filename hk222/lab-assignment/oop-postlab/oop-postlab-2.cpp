#include <iostream>

using namespace std;

template<class T> 
class Array2D 
{
private:
	int r;
	int c;
	T** arr;
public:
    Array2D(int r, int c);
    Array2D(int r, int c, T init);
    ~Array2D();

    Array2D& operator*(const Array2D & V); 
    T* operator[](int idx);
};

template<class T>
Array2D<T>::Array2D(int r, int c)
{
    arr = new T*[r];
    for (int i = 0; i < r; ++i)  arr[i] = new T[c];
}

template<class T>
Array2D<T>::Array2D(int r, int c, T init) : Array2D(r, c)
{
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            arr[i][j] = init;
        }
    }
}

template<class T>
Array2D<T>::~Array2D()
{
    for (int i = 0; i < r; ++i) delete[] arr[i];
    delete[] arr;
}

template<class T>
Array2D<T>& Array2D<T>::operator*(const Array2D<T>& V)
{
    Array2D<T>& res = new Array2D<T>(r, V.c, 0);
    
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < V.c; ++j)
        {
            for (int k = 0; k < c; ++k)
            {
                res->arr[i][j] += arr[i][k] * arr[k][j];
            }
        }
    }

    return *res;
}

template<class T>
T* Array2D<T>::operator[](int idx)
{
    return arr[idx];
}

int main() 
{
    Array2D<int>* p = new Array2D<int>(1, 2, 3);
    cout << (*p)[0][1] << endl;
    return 0;
}