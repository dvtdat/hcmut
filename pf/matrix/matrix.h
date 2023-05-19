#include <bits/stdc++.h>

using namespace std;

template <typename T>
class MyVector
{
private:
    T       *pD;
    int     nE, cap;
public:
    MyVector() : nE(0), cap(0), pD(nullptr) {}
    MyVector(unsigned int N) : nE(0), cap(N), pD(new T[N]) {}
    MyVector(const MyVector & V): nE(V.nE), cap(V.cap), pD(new T[V.cap])
    {
        // memcpy(pD, V.pD, sizeof(T) * nE);
        // TODO: what is the problem here?

        for (int i = 0; i < nE; ++i) pD[i] = V.pD[i];
    }

    MyVector(MyVector && V) : nE(V.nE), cap(V.cap), pD(V.pD)
    {
        V.cap = V.nE = 0;
        V.pD = nullptr;
    }

    ~MyVector()
    {
        clear();
    }

    MyVector& operator=(const MyVector & V)
    {
        clear();
        resize(V.cap);
        nE = V.nE;
        for (int i = 0; i < nE; ++i) pD[i] = V.pD[i];
        return *this;
    }

    MyVector& operator=(MyVector && V)
    {
        clear();
        pD = V.pD;
        cap = V.cap;
        nE = V.nE;
        V.pD = nullptr;
        V.cap = V.nE = 0;
        return *this;
    }

    void clear()
    {
        if (pD)
        {
            delete [] pD;
            pD = nullptr;
            cap = nE = 0;
        }
    }

    void resize(int N)
    {
        T *p = new T[N];
        if (nE > N) nE = N;
        if (pD)
        {
            for (int i = 0; i < nE; ++i) pD[i] = V.pD[i];
            delete [] pD;
            pD = nullptr;
        }
        cap = N;
        pD = p;
    }

    int size() const
    {
        return nE;
    }

    int getCap() const
    {
        return cap;
    }

    T& operator[](int idx) const
    {
        return pD[idx];
    }

    void push(const T & val)
    {
        if (nE - cap > 0) pD[nE++] = val;
        else
        {
            resize(nE + 1);
            pD[nE++] = val;
        }
    }

    void pop()
    {
        if (nE) nE--;
    }

    T& top()
    {
        return pD[nE - 1];
    }
};

class MyMatrix
{
    friend ostream & operator<<(ostream & os, const MyMatrix & m);
private:
    float **pD;
    int nR, nC;
public:
    MyMatrix() : nR(0), nC(0), pD(nullptr) {}
    MyMatrix(int nR, int nC);                       // constructor
    MyMatrix(const MyMatrix & M);                   // copy constructor
    MyMatrix(MyMatrix && M);                        // move constructor
    ~MyMatrix();                                    // destructor

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