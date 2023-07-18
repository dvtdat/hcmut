#include <bits/stdc++.h>

using namespace std;

const int N = 50;

struct BinTrie
{
    struct Node
    {
        int child[26];  // Edges between node, there are at most 26 edges starting from a single node, which is named from 'a' to 'z'.
        int exist;      // How many string are there that are represented by the current node.
        int cnt;        // How many string are there that have their prefix represented by the current node.
    } nodes[N];

    int cur;

    // Init the trie, setting up the first node with index of cur = 0.
    BinTrie() : cur(0)
    {
        memset(nodes[0].child, -1, sizeof(nodes[cur].child));
        nodes[0].exist = nodes[0].cnt = 0;
    };


    // Create a new node with the index of (cur + 1), init that node.
    int newNode()
    {
        cur++;
        memset(nodes[cur].child, -1, sizeof(nodes[cur].child));
        nodes[cur].exist = nodes[cur].cnt = 0;
        return cur;
    };

    void addString(string s)
    {
        int pos = 0;
        for (char f : s)
        {
            int c = f - 'a';
            
            // If there weren't not any child node for letter f, create a new node for it.
            if (nodes[pos].child[c] == -1) nodes[pos].child[c] == newNode();
            
            pos = nodes[pos].child[c];

            // There is one more string that have the prefix of the current node, adding to .cnt.
            nodes[pos].cnt++;
        }

        // There is a corresponding node for strign s, adding to .exist.
        nodes[pos].exist++;
    };

    bool deleteStringRecur(int pos, string &s, int i)
    {
        // If haven't found the string s yet, recur to the next children.
        if (i != (int)s.size())
        {
            int c = s[i] - 'a';
            bool isChildDeleted = deleteStringRecur(nodes[pos].child[c], s, i + 1);

            // If the child have being deleted, re-assign the .child to the init value.
            if (isChildDeleted) nodes[pos].child[c] = -1;
        }
        else nodes[pos].exist--;
        // If found the string s, decrease the .exist.

        if (pos != 0)
        {
            // If the current node is not the root, decrease the root's .cnt by 1 and check for haven't the string s been deleted yet.
            // If yes, then there is no string s can be represented by pos.

            nodes[pos].cnt--;
            if (nodes[pos].cnt == 0) return true;
        }
        return false;
    };

    void deleteString(string s)
    {
        if (!findString(s)) return;
        deleteStringRecur(0, s, 0);
    }

    bool findString(string s)
    {
        int pos = 0;
        for (char f : s)
        {
            int c = f - 'a';
            if (nodes[pos].child[c] == -1) return false;
            pos = nodes[pos].child[c];
        }
        
        // Checking for whether string s ended in this node.
        return (nodes[pos].exist != 0);
    }
};