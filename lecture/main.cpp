#include <bits/stdc++.h>

using namespace std;

struct LiNode {
    int val;
    LiNode *pNext;
};

void insertLiNode(LiNode* & pHead, int val, int idx)
{
    if (idx < 1)
    {
        LiNode *p = new LiNode;
        p->val = val;
        p->pNext = pHead;
        pHead = p;
        return;
    }

    LiNode *pPre = pHead;
    while (idx > 1 && pPre->pNext)
    {
        pPre = pPre->pNext;
        idx--;
    }

    LiNode *p = new LiNode;
    p->val = val;
    p->pNext = pPre->pNext;
    pPre->pNext = p;
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