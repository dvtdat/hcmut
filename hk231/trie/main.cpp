#include <bits/stdc++.h>

using namespace std;

#include <bits/stdc++.h>

using namespace std;

const int N = 100;
const int LG = 1;

struct BinTrie
{
    struct Node
    {
        int child[2];
        int exist, cnt;
    } nodes[N];

    int cur;
    BinTrie() : cur(0) 
    {
        memset(nodes[0].child, -1, sizeof(nodes[cur].child));
        nodes[0].exist = nodes[0].cnt = 0;
    }

    int newNode() 
    {
        cur++;
        memset(nodes[cur].child, -1, sizeof(nodes[cur].child));
        nodes[cur].exist = nodes[cur].cnt = 0;
        return cur;
    }

    void addNumber(int x) 
    {
        int pos = 0;
        for (int i = LG; i >= 0; i--)
        {
            int c = (x >> i) & 1;
            if (nodes[pos].child[c] == -1) nodes[pos].child[c] = newNode();
            pos = nodes[pos].child[c];
            nodes[pos].cnt++;
        }
        nodes[pos].exist++;
    }

    void deleteNumber(int x)
    {
        if (findNumber(x) == false) return;
        int pos = 0;
        for (int i = LG; i >= 0; i--)
        {
            int c = (x >> i) & 1;

            int tmp = nodes[pos].child[c];
            nodes[tmp].cnt--;

            if (nodes[tmp].cnt == 0)
            {
                nodes[pos].child[c] = -1;
                return;
            }

            pos = tmp;
        }
        nodes[pos].exist--;
    }

    bool findNumber(int x)
    {
        int pos = 0;
        for (int i = LG; i >= 0; i--)
        {
            int c = (x & (1 << i) ? 1 : 0);
            if (nodes[pos].child[c] == -1) return false;
            pos = nodes[pos].child[c];
        }
        return (nodes[pos].exist != 0);
    }
};

int main()
{
    vector<int> arr(5);
    arr[0] = 2;
    arr[1] = 9;
    arr[2] = 7;
    arr[3] = 5;
    arr[4] = 3;

    for (int s : arr) cout << s << ' ';
    cout << '\n';

    BinTrie myTrie;

    for (int i = 0; i < 5; ++i)
    {
        myTrie.addNumber(arr[i]);
    }
}