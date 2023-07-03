#include <bits/stdc++.h>

using namespace std;

struct LiNode {
    int val;
    LiNode *pNext;
    LiNode(int val, LiNode* &pN) : val(val), pNext(pN) {};
};

struct MyMatrix {
    friend ostream & operator<<(ostream & os, MyMatrix & n);
private:
    float **pD;
    int nR, nC;

public:
    MyMatrix() : nR(0), nC(0), pD(nullptr) {}           //default constructor
    MyMatrix(unsigned int nR, unsigned int nC);         //constructor
    ~MyMatrix();                                        //destructor

    int getNRows() { return nR; }
    int getNCols() { return nC; }

    float & at(int r, int c)
    {
        return pD[r][c];
    }

    MyMatrix operator*(MyMatrix & B);
    friend MyMatrix operator*(MyMatrix & B);
    MyMatrix operator*(float s);

    void Print();
};

MyMatrix::MyMatrix() 
{
    nR = nC = 0;
    pD = nullptr;
}

MyMatrix::MyMatrix(unsigned int nR, unsigned int nC)
{
    this->nR = nR;
    (*this).nC = nC;

#ifdef USING_MEMORY_LAYOUT_1
    pD = new float*[nR];
    *pD = new float[nR  * nC];
    for (int i = 1; i < nR; ++i) pD[i] = pD[i - 1] + nC;
#else
    pD = new float*[nR];
    for (int i = 0; i < nR; ++i) pD[i] = new float[nC];
#endif
}

MyMatrix::~MyMatrix()
{
#ifdef USING_MEMORY_LAYOUT_1
    delete [] *pD;
    delete [] pD;
#else
    for (int i = 0; i < nR; ++i) delete [] pD[i];
    delete [] pD;
#endif
}

MyMatrix operator*(float s, MyMatrix & B)
{   

}

ostream & operator<<(ostream & os, MyMatrix & n) {
    if (n.nR < 1 || n.nC < 1) return os;
    for (int i = 0; i < n.nR; ++i)
    {
        cout << n.pD[i][0];
        for (int j = 1; j < n.nC; ++j) cout << ' ' << n.pD[i][j];
        os << '\n';
    }

    return os;
}

void insertLiNode(LiNode* & pHead, int val, int idx)
{
    if (idx < 1)
    {
        // LiNode *p = new LiNode;
        // p->val = val;
        // p->pNext = pHead;
        // pHead = p;

        pHead = new LiNode(val, pHead);
        return;
    }

    LiNode *pPre = pHead;
    while (idx > 1 && pPre->pNext)
    {
        pPre = pPre->pNext;
        idx--;
    }

    pPre->pNext = new LiNode(val, pPre->pNext);

    // LiNode *p = new LiNode;
    // p->val = val;
    // p->pNext = pPre->pNext;
    // pPre->pNext = p;
}

void removeLiNode(LiNode* &pHead, int idx)
{
    if (!pHead) return;
    if (idx < 1)
    {
        LiNode *p = pHead;
        pHead = p->pNext;
        delete p;
        return;
    }

    LiNode *pPre = pHead;
    while (idx > 1 && pPre->pNext)
    {
        pPre = pPre->pNext;
        idx--;
    }

    LiNode *p = pPre->pNext;
    if (p) {
        pPre->pNext = p->pNext;
        delete p;
    }

}

int main()
{
    int N; cin >> N;

    LiNode *pHead = nullptr;
    for (int i = 0; i < N; ++i)
    {
        insertLiNode(pHead, i * 10, i);
    }

    for (LiNode *p = pHead; p; p = p->pNext)
    {
        cout << setw(5) << p->val;
    }
    cout << '\n';
    
    removeLiNode(pHead, 5);
    for (LiNode *p = pHead; p; p = p->pNext)
    {
        cout << setw(5) << p->val;
    }
    cout << '\n';
}