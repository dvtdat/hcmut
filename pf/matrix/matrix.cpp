#include "matrix.h"

MyMatrix::MyMatrix(int nR, int nC) : pD(nullptr)
{
    resize(nR, nC);
}

void MyMatrix::clear()
{
    if (!pD) return;
#ifdef USING_MEMORY_LAYOUT_1
    ...
#else
    for (int i = 0; i < nR; ++i) delete [] pD[i];
    delete [] pD;  
#endif
    pD = nullptr;
    nR = nC = 0;
}

void MyMatrix::resize(int R, int C)
{
    if (R == nR && C == nC) return;
    clear();
    nR = R;
    nC = C;
#ifdef USING_MEMORY_LAYOUT_1
    ...
#else
    pD = new float*[nR];
    for (int i =0; i < nR; ++i) pD[i] = new float[nC]; 
#endif
}
    
MyMatrix::~MyMatrix()
{
    clear();
}

MyMatrix::MyMatrix(const MyMatrix & M) : pD(nullptr)
{
    resize(M.nR, M.nC);
    for (int i = 0; i < nR; ++i)
    {
        for (int j = 0; j < nC; ++j)
        {
            pD[i][j] = M.pD[i][j];
        }
    }
}

MyMatrix::MyMatrix(MyMatrix &&M) : pD(M.pD), nR(M.nR), nC(M.nC)
{
    M.pD = nullptr;
    M.nR = M.nC = 0;
}

MyMatrix &MyMatrix::operator=(const MyMatrix &M)
{
    clear();
    resize(M.nR, M.nC);
    for (int i = 0; i < nR; ++i)
    {
        for (int j = 0; j < nC; ++j)
        {
            pD[i][j] = M.pD[i][j];
        }
    }

    return *this;
}

MyMatrix &MyMatrix::operator=(MyMatrix &&M)
{
    clear();
    nR = M.nR;
    nC = M.nC;
    pD = M.pD;

    M.nC = M.nR = 0;
    M.pD = nullptr;

    return *this;
}

ostream & operator<<(ostream & os, const MyMatrix & m)
{
    if (m.nR < 1 || m.nC < 1) return os;
    for (int i = 0; i < m.nR; ++i)
    {
        os << m.pD[i][0];
        for (int j = 1; j < m.nC; ++j) os << ' ' << m.pD[i][j];
        os << '\n';
    }
    return os;
}

MyMatrix MyMatrix::operator*(const MyMatrix & B)
{

}

MyMatrix MyMatrix::operator*(float s)
{

}

int main(int narg, char** argv)
{
    int nR, nC;

    stringstream ss("2 3");
    ss >> nR >> nC;

    MyMatrix mat(nR, nC);

    for (int i = 0; i < mat.getNRows(); ++i)
    {
        for (int j = 0; j < mat.getNCols(); ++i)
        {
            mat.at(i, j) = (rand() % 101) * 0.01f;
        }
    }

    cout << mat << '\n';
    MyMatrix B = (mat * 2.0f), C(mat);
    mat = std::move(B);

    cout << B << '\n';
}