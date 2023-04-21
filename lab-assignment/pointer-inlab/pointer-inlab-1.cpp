#include <iostream>

using namespace std;

int** readArray()
{
    int** ptr = new int*[10];
    
    for (int i = 0; i < 10; ++i)
    {
        ptr[i] = new int[10];

        for (int j = 0; j < 10; ++j)
        {
            cin >> ptr[i][j];
            if (ptr[i][j] == 0) 
            {
                for (int k = j; k < 10; ++k) ptr[i][k] = 0;
                break;
            }
        }
    }

    return ptr;
}

int main()
{
    int** matrix = readArray();
}