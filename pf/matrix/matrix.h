#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class MyMatrix
{
public:
    float **pD;
    int nR, nC;
public:
    MyMatrix() : nR(0), nC(0), pD(nullptr) {}
    MyMatrix(int nR, int nC);                       // constructor
    MyMatrix(const MyMatrix & M);                   // copy constructor
    ~MyMatrix();                                    // destructor

   MyMatrix(MyMatrix &&M);

    MyMatrix& operator=(const MyMatrix & M);        // copy assignment
    MyMatrix& operator=(MyMatrix && M);             // move assignment

    void clear();
    void resize(int R, int C);
    
    int getNRows() { return nR; }
    int getNCols() { return nC; }
    float * operator[](int row) const { return pD[row]; }
    float & at(int r, int c)
    {
        return pD[r][c];
    }
    const float & getAt(int r, int c) const { return pD[r][c]; }
    MyMatrix operator*(const MyMatrix & B);
    MyMatrix operator*(float s);
};

MyMatrix operator*(float s, const MyMatrix & B);
ostream & operator<<(ostream & os, const MyMatrix & m);